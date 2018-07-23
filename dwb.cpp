#include "dwb.h"
#include <QMessageBox>
#include <QDir>
#include <QDateTime>
#include <QTextStream>
int DWB::sign(float input)
{
	using namespace cv;
    if(input > 0) return 1;
    else if(input < 0) return -1;
    else return 0;
}

cv::Point DWB::WhitePointPositionIncrement(int input)
{
	using namespace cv;
    int x, y;
    Point p;
    x = y = 0;
    switch (input)
    {
    case 0:  x = 0;                 y = 0;                 break;
    case 1:  x = 0;                 y = (IMGRows / 4);     break;
    case 2:  x = 0;                 y = (IMGRows / 4) * 2; break;
    case 3:  x = 0;                 y = (IMGRows / 4) * 3; break;
    case 4:  x = (IMGCols / 4);     y = 0;                 break;
    case 5:  x = (IMGCols / 4);     y = (IMGRows / 4);     break;
    case 6:  x = (IMGCols / 4);     y = (IMGRows / 4) * 2; break;
    case 7:  x = (IMGCols / 4);     y = (IMGRows / 4) * 3; break;
    case 8:  x = (IMGCols / 4) * 2; y = 0;                 break;
    case 9:  x = (IMGCols / 4) * 2; y = (IMGRows / 4);     break;
    case 10: x = (IMGCols / 4) * 2; y = (IMGRows / 4) * 2; break;
    case 11: x = (IMGCols / 4) * 2; y = (IMGRows / 4) * 3; break;
    case 12: x = (IMGCols / 4) * 3; y = 0;                 break;
    case 13: x = (IMGCols / 4) * 3; y = (IMGRows / 4);     break;
    case 14: x = (IMGCols / 4) * 3; y = (IMGRows / 4) * 2; break;
    case 15: x = (IMGCols / 4) * 3; y = (IMGRows / 4) * 3; break;
    default:                                               break;
    }
    p.x = x;
    p.y = y;
    return p;
}

//RGB空间到YCrCb空间的转换公式
// Y = 0.299R + 0.587G + 0.114B
//Cr = 0.5R - 0.419G - 0.081B
//Cb = -0.169R - 0.331G + 0.5B
void DWB::RGB2YCrCb(cv::Mat MR, cv::Mat MG, cv::Mat MB, cv::Mat MY, cv::Mat MCr,cv::Mat MCb)
{
	using namespace cv;
    int Mrows, Mcols; //RGB和YCrCb空间矩阵的行列数
    Mrows = MR.rows;
    Mcols = MR.cols;
    MY.create(IMGRows, IMGCols, CV_32FC1);

    //转换公式用到的系数
    Mat Y_Rpara(Mrows, Mcols, CV_32FC1, Scalar::all(0.299));
    Mat Y_Gpara(Mrows, Mcols, CV_32FC1, Scalar::all(0.587));
    Mat Y_Bpara(Mrows, Mcols, CV_32FC1, Scalar::all(0.114));
    Mat Cr_Rpara(Mrows, Mcols, CV_32FC1, Scalar::all(0.5));
    Mat Cr_Gpara(Mrows, Mcols, CV_32FC1, Scalar::all(0.419));
    Mat Cr_Bpara(Mrows, Mcols, CV_32FC1, Scalar::all(0.081));
    Mat Cb_Rpara(Mrows, Mcols, CV_32FC1, Scalar::all(0.169));
    Mat Cb_Gpara(Mrows, Mcols, CV_32FC1, Scalar::all(0.331));
    Mat Cb_Bpara(Mrows, Mcols, CV_32FC1, Scalar::all(0.5));

    MY = MR.mul(Y_Rpara) + MG.mul(Y_Gpara) + MB.mul(Y_Bpara);
    MCr = MR.mul(Cr_Rpara) - MG.mul(Cr_Gpara) - MB.mul(Cr_Bpara);
    MCb = -MR.mul(Cb_Rpara) - MG.mul(Cb_Gpara) + MB.mul(Cb_Bpara);
    return;
}

void DWB::SizeAdjust()
{
    IMGRows = src.rows;
    IMGCols = src.cols;
    if((IMGRows % 4 != 0) || (IMGCols % 4) != 0)
    {
        IMGRows -= IMGRows % 4;
        IMGCols -= IMGCols % 4;
        src = src(cv::Rect(0, 0, IMGCols, IMGRows));
    }
    return;
}

void DWB::VideoCapture()
{

	//using namespace cv;
	//cv::VideoCapture videoCapture(0);
	//videoCapture.set(CAP_PROP_FRAME_HEIGHT, 3264);
	//videoCapture.set(CAP_PROP_FRAME_WIDTH, 2448);
	//videoCapture.set(CAP_PROP_EXPOSURE, -10);

	//float exValue = -10;
	//Mat frame;
	//while (1)
	//{
	//	videoCapture.set(CAP_PROP_EXPOSURE, exValue);
	//	videoCapture >> frame;


	//	imshow("frame", frame);
	//	exValue = exValue + 0.1;
	//	cout << "exValue:" << exValue << endl;
	//	waitKey(100);
	//}

}

int DWB::SpaceChange(cv::Mat Input)
{
    src = Input;
    SizeAdjust();
    split(src, RGBChannels);

    B = RGBChannels.at(0);
    G = RGBChannels.at(1);
    R = RGBChannels.at(2);
    B.convertTo(B, CV_32FC1);
    G.convertTo(G, CV_32FC1);
    R.convertTo(R, CV_32FC1);
    Y.create(IMGRows, IMGCols, CV_32FC1);//为Y Cr Cb开辟空间
    Cb.create(IMGRows, IMGCols, CV_32FC1);
    Cr.create(IMGRows, IMGCols, CV_32FC1);
    RGB2YCrCb(R, G, B, Y, Cr, Cb);
    return 1;
}

int DWB::CRCBBlocking()
{
	using namespace cv;
    Mat CrClone = Cr.clone(); // ROI和父图像共享缓冲区，利用克隆图像操作不影响原CR、CB
    Mat CbClone = Cb.clone();
    for(int x = 0; x < IMGCols; x += (IMGCols / 4))
    {
        for(int y = 0; y < IMGRows; y += (IMGRows / 4))
        {
            CrPlot = CrClone(Rect(x, y, (IMGCols / 4), (IMGRows / 4)));
            CbPlot = CbClone(Rect(x, y, (IMGCols / 4), (IMGRows / 4)));
            vCrPlot.push_back(CrPlot);
            vCbPlot.push_back(CbPlot);
        }
    }
	if (vCrPlot.size() == 0)
		throw runtime_error("vCrPlot empty, line 140, CRCBBlocking");
	if (vCbPlot.size() == 0)
		throw runtime_error("vCbPlot empty, line 140, CRCBBlocking");
    return 1;
}

int DWB::ParaCal()
{
	using namespace cv;
    Mat MDb, MDr;
    Scalar MeanValue;
    Scalar DifferValue;
    float MbValue, MrValue, DbValue, DrValue;
    N = ((IMGRows / 4)) * ((IMGCols / 4));
    MDb.create((IMGRows / 4), (IMGCols / 4), CV_32FC1);
    MDr.create((IMGRows / 4), (IMGCols / 4), CV_32FC1);

    for(int i = 0; i < (int)vCrPlot.size(); i++)
    {
        //提取各块
        CbPlot = vCbPlot.at(i);
        //计算MB、DB，并存于VMB、VDB中;计算MR、DR，并存于VMR、VDR中。计算公式
        //DB = ∑(|CB(i,j) - MB|)/N，将|CB(i,j) - MB|矩阵命名为MDB
        //DR = ∑(|CR(i,j) - MR|)/N，将|CR(i,j) - MR|矩阵命名为MDR
        MeanValue = mean(CbPlot);
        Mb = MeanValue.val[0];
        vMb.push_back(Mb);
        for(int x = 0; x < MDb.rows; x++)
        {
            float* pMDb = MDb.ptr<float>(x);
            float* pCbPlot = CbPlot.ptr<float>(x);
            for(int y = 0; y < MDb.cols; y++)
            {
               pMDb[y] = abs(pCbPlot[y] - Mb);
            }
        }
        DifferValue = sum(MDb);
        Db = DifferValue.val[0] / N;
        vDb.push_back(Db);

        CrPlot = vCrPlot.at(i);
        MeanValue = mean(CrPlot);
        Mr = MeanValue.val[0];
        vMr.push_back(Mr);
        for(int x = 0; x < MDr.rows; x++)
        {
            float* pMDr = MDr.ptr<float>(x);
            float* pCrPlot = CrPlot.ptr<float>(x);
            for(int y = 0; y < MDr.cols; y++)
            {
               pMDr[y] = abs(pCrPlot[y] - Mr);
            }
        }
        DifferValue = sum(MDr);
        Dr = DifferValue.val[0] / N;
        vDr.push_back(Dr);
    }

    Mb = Mr = Db = Dr = 0;
    for(int i = 0; i < 16; i++)
    {
        MbValue = vMb.at(i);//各块的MB MR DB DR值
        MrValue = vMr.at(i);
        DbValue = vDb.at(i);
        DrValue = vDr.at(i);
        if(DbValue >= 1 && DrValue >= 1) //满足阈值判断
        {
            Mb += MbValue;
            Mr += MrValue;
            Db += DbValue;
            Dr += DrValue;
            PreserveNO.push_back(i);
        }
        else
		{
			cout << "white is too small" << endl;
			continue;
		}
    }
    Mb /= PreserveNO.size();
    Mr /= PreserveNO.size();
    Db /= PreserveNO.size();
    Dr /= PreserveNO.size();

	if (PreserveNO.size() == 0)
		throw runtime_error("PreserveNO, line 224, ParaCal");
    return 1;
}


// 计算公式：
// |CB(i,j) - (MB + DB * sign(MB))| < 1.5 * DB;
// |CR(i,j) - (1.5 * MR + DR * sign(MR))| < 1.5 * DR
// 将 (MB + DB * sign(MB)) 命名为BB
// 将 (1.5 * MR + DR * sign(MR)) 命名为RR
int DWB::WhiteRigionSel()
{
	using namespace cv;
    float Bb, Rr;
    int NO = 0; //满足阈值选择的块编号
    float WhitePointValue;
    Point Increment;

    Bb = Mb + Db * sign(Mb);
    Rr = 1.5 * Mr + Dr * sign(Mr);
    for(int i = 0; i < (int)PreserveNO.size(); i++)
    {
        NO = PreserveNO.at(i);
        CbPlot = vCbPlot.at(NO);
        CrPlot = vCrPlot.at(NO);
        Increment = WhitePointPositionIncrement(NO);

        for(int a = 0; a < (IMGRows / 4); a++)
        {
            float* pCbPlot = CbPlot.ptr<float>(a);
            float* pCrPlot = CrPlot.ptr<float>(a);
            for(int b = 0; b < (IMGCols / 4); b++)
            {
               pCbPlot[b] = abs(pCbPlot[b] - Bb) - 1.5 * Db;
               pCrPlot[b] = abs(pCrPlot[b] - Rr) - 1.5 * Dr;
               if((pCbPlot[b] < 0) && (pCrPlot[b] < 0))
               {
                   WhitePoint.x = b + Increment.x; //参考白点的绝对坐标
                   WhitePoint.y = a + Increment.y;
                   if(WhitePoint.x > IMGCols || WhitePoint.y > IMGRows)
                   {
                       cout << "out of boundary! " << endl;
                   }
                   else
                   {
                         WhitePointSet.push_back(WhitePoint); //参考白点的坐标
                         WhitePointValue = Y.at<float>(WhitePoint.y, WhitePoint.x);
                         WhitePointY.push_back(WhitePointValue); //参考白点的值
                   }
               }
               else
			   {
				   //cout << "not satistafy" << endl;
				   continue;
			   }
                   
            }
        }
    }

	if (WhitePointSet.size() == 0)
		throw runtime_error("WhitePointSet is empty, line 284, WhiteRigionSel");
    return 0;
}

int DWB::Distinguish()
{
	using namespace cv;
    float YY = 0;
    DistinguishY = Mat::zeros(Size(IMGCols, IMGRows),CV_32FC1);
    for(int i = 0; i < (int)WhitePointSet.size(); i++)
    {
        WhitePoint = WhitePointSet.at(i);
        DistinguishY.at<float>(WhitePoint.y, WhitePoint.x) = WhitePointY.at(i);
    }

    //使用前一百个点的均值
	int firstPer = WhitePointY.size() * 0.1;

    for(int i = WhitePointY.size() - 1; i >= WhitePointY.size() - firstPer; i--)
    {
        YY += WhitePointY.at(i);
    }
    YY /= firstPer;

    for(int a = 0; a < DistinguishY.rows; a++)
    {
        float* pDis = DistinguishY.ptr<float>(a);
        for(int b = 0; b < DistinguishY.cols; b++)
        {
            if(pDis[b] > YY) pDis[b] = 1;
            else pDis[b] = 0;
        }
    }
    return 1;
}

void DWB::GetGain()
{
	using namespace cv;
    Mat R2, G2, B2;
    float Ravg, Gavg, Bavg;
    float RSumValue, GSumValue, BSumValue;
    int RNonZero, GNonZero, BNonZero; //R2 G2 B2 中非0元素个数
    Scalar RSum, GSum, BSum;
    double YMax, YMin;

    R2 = R.mul(DistinguishY);
    B2 = B.mul(DistinguishY);
    G2 = G.mul(DistinguishY);

    RNonZero = countNonZero(R2);
    RSum = sum(R2);
    RSumValue = RSum.val[0];
    GNonZero = countNonZero(G2);
    GSum = sum(G2);
    GSumValue = GSum.val[0];
    BNonZero = countNonZero(B2);
    BSum = sum(B2);
    BSumValue = BSum.val[0];

    Ravg = RSumValue / RNonZero;
    Gavg = GSumValue / GNonZero;
    Bavg = BSumValue / BNonZero;

    minMaxIdx(Y,&YMin,&YMax);

    Gain.RG = YMax / Ravg;
    Gain.GG = YMax / Gavg;
    Gain.BG = YMax / Bavg;

    return ;
}

RGBGain DWB::operator =(const RGBGain &R) const
{
    RGBGain gain;
    gain.RG = R.RG;
    gain.GG = R.GG;
    gain.BG = R.BG;
    return gain;
}

RGBGain DWB::getRGBGain()
{
	return Gain;
}

int DWB::ClearAll()
{
	RGBChannels.clear();
	YCbCrChannels.clear();
	vCbPlot.clear();
	vCrPlot.clear();
	vMb.clear();
	vMr.clear();
	vDb.clear();
	vDr.clear();
	WhitePointY.clear();
	PreserveNO.clear();
	WhitePointSet.clear();
	return 0;
}
bool debug = 0;
int DWB::threshImgSelectWhite(vector<cv::Mat> &vecWhite, cv::Mat &img)
{
	using namespace cv;
	
	//***************匿名处理函数**************************//
	auto checkRoi = [](Rect &bRect, Mat &cutImg)
	{
		
		if (bRect.x > cutImg.cols)
			bRect.x = cutImg.cols - 1;
		if (bRect.y > cutImg.rows)
			bRect.y = cutImg.rows - 1;

		if ((bRect.x + bRect.width) > cutImg.cols)
			bRect.width = cutImg.cols - bRect.x;
		if ((bRect.y + bRect.height) > cutImg.rows)
			bRect.height = cutImg.rows - bRect.y;
	};
	auto getRois = [checkRoi](vector<cv::Mat> &roiVec, vector<vector<Point>> &vecRegion, Mat &src)
	{
		for (int i = 0; i< vecRegion.size(); i++)
		{
			if (vecRegion[i].size() < 50)
				continue;
			Rect bRect = boundingRect(vecRegion[i]);
			checkRoi(bRect, src);
			Mat img(src, bRect);
			roiVec.push_back(img);
		}
	};
	auto merageRoi = [](vector<cv::Mat> &roiVec, Mat &merImg)
	{
		int addCols = 0;
		int addRows = 0;
		for (int i = 0; i < roiVec.size(); i++)
		{
			addCols = addCols + roiVec[i].cols;
			//addRows = addRows + roiVec[i].rows;
			if (roiVec[i].rows > addRows)
				addRows = roiVec[i].rows;
		}

		Mat img = Mat::zeros(addRows, addCols, CV_8UC3);

		int ii = 0;
		int jj = 0;
		int startii = 0;
		for (int index = 0; index < roiVec.size(); index++)
		{
			//每张图拼接在一起
			Mat roi = roiVec[index];

			if (debug)
			{
				imshow("roi", roi);
				waitKey(1);
			}
			
			for (int j = 0, jj = 0; j < roi.rows; j++, jj++)
			{
				for (int i = 0, ii = startii; i < roi.cols; i++, ii++)
				{
					if (jj > addRows - 1 || ii > addCols - 1)
					{
						cout << "out of addRow or addCols" << endl;
						continue;
					}
					*(img.ptr(jj, ii) + 0) = *(roi.ptr(j, i) + 0);
					*(img.ptr(jj, ii) + 1) = *(roi.ptr(j, i) + 1);
					*(img.ptr(jj, ii) + 2) = *(roi.ptr(j, i) + 2);
					if (debug)
					{
			//			imshow("roiImg", img);
			//			waitKey(1);
					}
				}
			}
			startii = startii + roi.cols;

			merImg = img;
			if (debug)
			{
				imshow("merimg", merImg);
				waitKey(1);
			}
		}
	};

	/******************************************************************************************/
	//正式处理部分
	Mat ouImg;
	Mat inImg = img.clone();
	cvtColor(inImg, inImg, CV_RGB2GRAY);
	vector<Point> roiPoint;
	threshold(inImg, ouImg, 125, 255, THRESH_BINARY);
	//获取轮廓
	vector<vector<Point>> vecRegion;
	findContours(ouImg, vecRegion, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	if (vecRegion.size() == 0)
	{
		return -1;
	}
	vector<Mat> roiVec;
	Mat merageImg;
	getRois(roiVec, vecRegion, img);
	merageRoi(roiVec, merageImg);
	vecWhite.push_back(merageImg);
}
void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QString text;
	switch (type)
	{
	case QtDebugMsg:
		text = QString("Debug:");
		break;

	case QtWarningMsg:
		text = QString("Warning:");
		break;

	case QtCriticalMsg:
		text = QString("Critical:");
		break;

	case QtFatalMsg:
		text = QString("Fatal:");
	}

	QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
	QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
	QString current_date = QString("(%1)").arg(current_date_time);
	QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

	QFile file("log.txt");
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream text_stream(&file);
	text_stream << message << "\r\n";
	file.flush();
	file.close();
}
RGBGain DWB::DynamicWB(cv::Mat InputIMG)
{
	
	try 
	{
		cv::Mat input = InputIMG;
		//vector<cv::Mat> vecWhite;
		//threshImgSelectWhite(vecWhite, input);
		SpaceChange(input);
		
		CRCBBlocking();
		ParaCal();
		WhiteRigionSel();
		Distinguish();
		GetGain();
		ClearAll();
	}
	catch(const runtime_error& e)
	{
		qInstallMessageHandler(outputMessage);
		qCritical(e.what());
	};

    return Gain;
}