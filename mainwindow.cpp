#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"ui_Widget.h"
#include <thread>
#include <chrono>
#include <QDir>
#include <QDateTime>
#include <QMessageBox>
#include <Objbase.h>
#include <tinyxml2.h>
#include <QCompleter>
#include <QAxObject>
#include "excelengine.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
using namespace tinyxml2;
void outputMessageX(QtMsgType type, const QMessageLogContext &context, const QString &msg)
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
MainWindow::MainWindow(QString usr,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),mCameraCount(0),
    mThreadCond(false),mDisplayCond(true)
{

	dwb.VideoCapture();
	
	this->musrName = usr;
    ui->setupUi(this);


	CoInitialize(NULL);
    mStartup = QApplication::applicationDirPath();
	if (!loadConfig())
	{
		return;
	}
#define MAX_LIGHT (8)
	QSlider* slides[MAX_LIGHT] = {ui->slideLight1 ,ui->slideLight2,ui->slideLight3,ui->slideLight4,
		ui->slideLight5,ui->slideLight6,ui->slideLight7,ui->slideLight8};
	for (int j = 0; j < MAX_LIGHT; j++)
	{
		slides[j]->setRange(0, 256);
	}
	if (0 != mLightCtrl.open(mLightPort.c_str(), mBaudRate, mDataBits, mStopBits, mParity))
	{
		showMessage(QStringLiteral("光源控制端口打开失败!"));
		//return;
	}
	if (initCameras())
	{
		for (int i = 0; i < mCameraCount; i++)
		{
			mImages[i] = new unsigned char[MAX_BUFFER_SIZE];
		}
		startThread();
		connect(this, &MainWindow::displaySig, this, &MainWindow::onDisplay);
	}
	
	int res = mMotionCard.open();
	if (0 >= res)
	{
		showMessage(QStringLiteral("未找到运动控制卡!"));
	}

	uiFrom.setupUi(&qw);
	connect(uiFrom.pushButton_3, SIGNAL(clicked()), this, SLOT(ensure()));
	
	QStringList strlist;
	for (int i = 0; i < 7; i++) {
		QString str= QString::number(i + 1, 10);
		uiFrom.comboBox->addItem(str);
	}
	QStringList tb_list_h;
	tb_list_h << QString::fromLocal8Bit("第一面")<< "" << QString::fromLocal8Bit("第二面")<< "" << QString::fromLocal8Bit("第三面") <<""<<
		QString::fromLocal8Bit("第四面")<<"" << QString::fromLocal8Bit("第五面")<<"" << QString::fromLocal8Bit("第六面")<<"";
	QStringList tb_list_v;
	tb_list_v << "" << "" << "" << "" << "" << "" << "" << "";

	ui->tableWidget->setRowCount(8);
	ui->tableWidget->setColumnCount(12);
	ui->tableWidget->setHorizontalHeaderLabels(tb_list_h);
	ui->tableWidget->setVerticalHeaderLabels(tb_list_v);
	ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

	int column = ui->tableWidget->columnCount();
	int row = ui->tableWidget->rowCount();
	
	//ui->tableWidget->setColumnWidth(0, 100);
	//ui->tableWidget->setColumnWidth(1, 100);


	ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	//ui->tableWidget->horizontalHeader()->setVisible(false);
	
	for (int i = 0; i < column; i=i+2) 
	{
		for (int j = 0; j < row; j++) 
		{
			QCheckBox *qcb = new QCheckBox();
			ui->tableWidget->setCellWidget(j, i, qcb);
		}
	}

	//for (int i = 0; i < row; j++) 
	//{

	//}
	for (int k = 0; k < column; k = k+ 2 ) {
		ui->tableWidget->rowSpan(0,k);
		QString str = QString::fromLocal8Bit("第");
		str = str + (k + 1);
		str = str + QString::fromLocal8Bit("面");
		ui->tableWidget->setItem(0, k, &QTableWidgetItem("dsdf"));
	}

	//设置文件保存路径
	pathUi.setupUi(&qwPath);
	connect(pathUi.pushButton, SIGNAL(clicked()), this, SLOT(alsetPath()));
	pathUi.taskLineEdit->setText(getTime("yyMMdd-"));
	pathUi.usrLineEdit->setText (musrName);
	pathUi.zuheLineEdit->setText("zuhe");
}

#include <QThread>
MainWindow::~MainWindow()
{
    mThreadCond = false;
    QThread::msleep(500);//500
	mLightCtrl.close();
	for (int i = 0; i < DISPLAY_CAMERA_COUNT; i++)
	{
		delete[] mImages[i];
		mImages[i] = nullptr;
	}
    delete ui;
	CoUninitialize();
}

void MainWindow::setRgain(int param)
{
	
}

void MainWindow::setGgain(int param)
{
}

void MainWindow::setBgain(int param)
{
}

void MainWindow::isOpenAWB(int param)
{
	if (param == 2) 
	{
		isOpenAWBmode = true;
	}
	else 
	{
		isOpenAWBmode = false;
	}
}

void MainWindow::setGainValue()
{
	isOpenAWBmode = false;
	ui->checkBox->setCheckState(Qt::Unchecked);
}

void MainWindow::OpenOrCloseAWB(bool state)
{
	startAWB = state;
}

void MainWindow::addElement()
{
	QString str = ui->cmbClassify->currentText();
	string chn = str.toStdString();

	string eng = mClassify[chn];

	if(eng == "")
	{
		showMessage(QStringLiteral("无法添加商品， 原因:找不到对应中文名的商品!"));
		return;
	}

	string seq = mEn2Seq[eng];

	productinfo product = { eng, chn, 0, 0};
	product.seqcode = seq;
	products.push_back(product);
	
	QStringList q_str_list;
	for (int i = 0; i < products.size(); i++) {
		q_str_list << QString(products[i].chn.c_str());
	}
	ui->tableWidget->setVerticalHeaderLabels(q_str_list);
	qw.show();


	//auto writeLable = [&chn, &eng](QString path)
	//{
	//	QFile lableFile(path);
	//	if (!lableFile.open(QIODevice::Text | QIODevice::OpenModeFlag::Append | QIODevice::OpenModeFlag::ReadWrite)) {
	//		cout << "Can't open the file!" << endl;
	//		return -1;
	//	}
	//	//if(lableFile)

	//	QTextStream out(&lableFile);
	//	out.seek(0);
	//	QString startStr = out.readLine();
	//	if (startStr.isEmpty()) {
	//		lableFile.write(eng.c_str());
	//	}
	//	else
	//	{
	//		//out.seek(lableFile.atEnd());
	//		lableFile.write(("\n"+eng).c_str());
	//	}
	//	lableFile.close();
	//	return 0;
	//};

	//writeLable(QString("lable.txt"));
}

void MainWindow::ensure()
{
	int end = products.size() - 1;
	products[end].proNum = uiFrom.comboBox->currentText().toInt();
	qw.hide();
	uiFrom.comboBox->setCurrentIndex(0);
}

void MainWindow::SelectionChanged()
{
	//QTableWidgetItem *item = ui->tableWidget->currentItem();
	//int row = item->row();
	//int col = item->column();

	//vector<int> point;
	//point.push_back(row);
	//point.push_back(col);

	//countItem.push_back(point);
	
	//QStringList listh;
	//listh << QString::fromLocal8Bit("第一面") << "第二面" << "第三面";
	//ui->tableWidget->setHorizontalHeaderLabels(listh);

	//QStringList listw;
	//listw << QString::fromLocal8Bit("趣多多1122333");
	//ui->tableWidget->setVerticalHeaderLabels(listw);
	//item->setSelected(true);
}

void MainWindow::addItem()
{

	//获取数据，并且记录到界面上

	if(products.size()==1)
	{
		pathUi.zuheLineEdit->setText(products[0].eng.c_str());
	}
	qwPath.show();
}

void MainWindow::clearItem()
{

	auto clearTable = [](vector<productinfo> & pdinf, QTableWidget *tableWidget)
	{
		
		for (int i = 0; i < pdinf.size(); i++)
		{

			for (int j = 0; j < pdinf[i].statistic.size(); j++)
			{
				QString str = pdinf[i].statistic[j];
				//tableWidget->setItem(0, 1, new QTableWidgetItem("180"));
				tableWidget->setItem(i, j * 2 + 1, new QTableWidgetItem(""));
			}
		}
		pdinf.clear();
	};
	QTableWidget *tableWidget = ui->tableWidget;
	clearTable(products, tableWidget);
	QStringList tb_list_v;
	tb_list_v << "" << "" << "" << "" << "" << "" << "" <<"";
	ui->tableWidget->setVerticalHeaderLabels(tb_list_v);
	showMessage(QStringLiteral("清空需要统计的商品!"));
}

void MainWindow::currentItem(QTableWidgetItem * item)
{
	//item->setBackground(QBrush(QColor(50, 50, 50)));
}

void MainWindow::alsetPath()
{
	ExcelEngine excel2;
	vector<vector<QString>> table;
	QTableWidget *tableWidget = ui->tableWidget;
	auto takeInfo = [&excel2](vector<vector<QString>> &table, QString path, vector<productinfo> & pdinf)
	{
		QString fileName = path + "/count.xls";
		QFile file(fileName);
		if (file.exists()) {
			cout << "exists" << endl;
		}
		//excel2(QObject::tr(fileName.toStdString().c_str())); //创建
		excel2.Open(QObject::tr(fileName.toStdString().c_str()));

		excel2.ReadDataToVector(table);

		//判断products在excel中有无，有则不处理，无则增加
		vector<vector<QString>> addrow;
		for (int i = 0; i < pdinf.size(); i++)
		{
			bool isExist = false;

			for (int j = 1; j < table.size(); j++)
			{
				QString str = table[j][0];
				QString str1 = QString::fromStdString(pdinf[i].chn);
				if (str.compare(str1) == 0)
				{
					isExist = true;
					break;
				}
			}
			if (!isExist)
			{
				vector<QString> newType;
				newType.push_back(QString::fromStdString(pdinf[i].chn));
				for (int k = 0; k < 6; k++)
				{
					newType.push_back("0");
				}
				table.push_back(newType);
				addrow.push_back(newType);
			}
		}
		//excel2.ReadDataToTable(ui->tableWidget);

		for (int i = 0; i < addrow.size(); i++)
		{
			for (int j = 0; j < addrow[i].size(); j++)
			{
				excel2.SetCellData(i + excel2.GetRowCount()+1 , j + 1, QVariant(addrow[i][j]));
			}
		}
		excel2.Save(); //保存
		excel2.Close();
	};




	auto record2UiTable = [&table](QTableWidget *tableWidget, vector<productinfo> & pdinf)
	{
		int rows = tableWidget->rowCount();
		int cols = tableWidget->columnCount();

		for (int i = 0; i < pdinf.size(); i++)
		{
			for (int j = 0; j < table.size(); j++)
			{
				QString chn = QString::fromStdString(pdinf[i].chn);
				QString chnt = table[j][0];
				if (chn.compare(chnt) == 0)
				{
					for (int k = 1; k < table[j].size(); k++)
					{
						pdinf[i].statistic.push_back(table[j][k]);
					}
				}
			}
		}
	};




	auto showData = [](QTableWidget *tableWidget, vector<productinfo> & pdinf)
	{
		for (int i = 0; i < pdinf.size(); i++)
		{

			for (int j = 0; j < pdinf[i].statistic.size(); j++)
			{
				QString str = pdinf[i].statistic[j];
				//tableWidget->setItem(0, 1, new QTableWidgetItem("180"));
				tableWidget->setItem(i, j * 2 + 1, new QTableWidgetItem(str));
			}
		}
	};


	auto saveJson = [](vector<productinfo> & pdinf, QString path)
	{

		QJsonDocument document;
		QJsonObject arrayAll;
		QJsonArray jsArray;

		for (int i = 0; i < pdinf.size(); i++)
		{
			QJsonObject json;
			QString str = QString::fromStdString(pdinf[i].chn);
			json.insert(QString("eng"), QString::fromStdString(pdinf[i].eng));
			json.insert(QString("chn"), QString::fromStdString(pdinf[i].chn));
			//json.insert(QString("Seqcode"), QString::fromStdString(pdinf[i].seqcode));
			json.insert(QString("num"), QString::number(pdinf[i].proNum));
			//document.setObject(json);
			//jsArray.push_back(json);
			arrayAll.insert(QString::fromStdString(pdinf[i].seqcode), json);
		}

		//string str = arrayAll;
		QString strJson = QString(QJsonDocument(arrayAll).toJson());

		QFile js(path);
		if (!js.open(QIODevice::Text | QIODevice::WriteOnly)) {
			cout << "Can't open the file!" << endl;
			return -1;
		}
		js.write(strJson.toStdString().c_str());
	};




	auto writeLable = [](QString path, vector<productinfo> &pdinf)
	{
		QFile lableFile(path);
		if (!lableFile.open(QIODevice::Text | QIODevice::OpenModeFlag::Append | QIODevice::OpenModeFlag::ReadWrite)) {
			cout << "Can't open the file!" << endl;
			return -1;
		}
		//if(lableFile)

		for (int i = 0; i<pdinf.size(); i++)
		{
			string eng = pdinf[i].eng;
			QTextStream out(&lableFile);
			out.seek(0);
			QString startStr = out.readLine();
			if (startStr.isEmpty()) {
				lableFile.write(eng.c_str());
			}
			else
			{
				//out.seek(lableFile.atEnd());
				lableFile.write(("\n" + eng).c_str());
			}
		}

		lableFile.close();
		return 0;
	};

	if (products.size() > 1) 
	{
		takeInfo(table, mStartup, products);
		record2UiTable(tableWidget, products);
	}
	QString path = getPath() + "/";
	mkMutiDir(path);
	saveJson(products, path + "label.txt");
	writeLable(path + "old_label.txt", products);
	showData(tableWidget, products);
	qwPath.hide();
	ui->genPathLabel->setText(QString::fromLocal8Bit("图片保存路径:") + path);
	showMessage(QStringLiteral("成功加入需要统计的商品的格子!"));
}

bool MainWindow::loadConfig()
{
	bool ret = true;
	tinyxml2::XMLDocument doc;
	if (XML_SUCCESS == doc.LoadFile("classify.xml"))
	{
		XMLElement* collection = doc.RootElement();
		if (collection)
		{
			XMLElement* product = collection->FirstChildElement();
			ui->cmbClassify->setEditable(true);
			QStringList cnNames;
			while (product)
			{
				XMLElement* eng = product->FirstChildElement("eng");
				XMLElement* cn = product->FirstChildElement("chn");
				XMLElement* seq = product->FirstChildElement("Seqcode");
				if (eng && cn)
				{
					const char* cnName = cn->GetText();
					const char* enName = eng->GetText();
					const char* seqName = seq->GetText();

					mClassify[cnName] = enName;
					mEn2Cn[enName] = cnName;
					mEn2Seq[enName] = seqName;

					cnNames.push_back(cnName);
					ui->cmbClassify->addItem(cnName);
				}
				product = product->NextSiblingElement();
			}
			QCompleter* pComplete = new QCompleter(cnNames, this);
			ui->cmbClassify->setCompleter(pComplete);
			pComplete->setFilterMode(Qt::MatchContains);
		}
	}
	else
	{
		showMessage(QStringLiteral("检查类别文件!"));
		ret = false;
	}

	tinyxml2::XMLDocument doc2;
	if (XML_SUCCESS == doc2.LoadFile("config.xml"))
	{
		XMLElement* settings = doc2.RootElement();
		if (settings)
		{
			XMLElement* light = settings->FirstChildElement("light");
			XMLElement* motion = settings->FirstChildElement("motioncontrol");
			if (light && motion)
			{
				mLightPort = light->Attribute("port");
				mBaudRate = atoi(light->Attribute("BaudRate"));
				mDataBits = atoi(light->Attribute("DataBits"));
				mStopBits = atoi(light->Attribute("StopBits"));
				mParity = atoi(light->Attribute("Parity"));

				mMotionVel = atoi(motion->Attribute("vel"));
				mPulsePerAngle = atoi(motion->Attribute("pulsperangle"));
			}
			else { ret = false; }
		}
		else
		{
			ret = false;
		}
	}
	else
	{
		showMessage(QStringLiteral("检查配置文件!"));
		ret = false;
	}
	return ret;
}

void MainWindow::showMessage(QString msg)
{
	QMessageBox msgBox;
	msgBox.setText(msg);
	msgBox.exec();
}

bool MainWindow::initCameras()
{
	mUcm = UsbCameraManager::instance();
    int i=0;

	mGraphicsViews[0] = ui->graphicsView;
	mGraphicsViews[1] = ui->graphicsView2;
	mGraphicsViews[2] = ui->graphicsView3;
	mGraphicsViews[3] = ui->graphicsView4;
	for (i = 0; i < DISPLAY_CAMERA_COUNT; i++)
	{
		mScenes[i] = new QGraphicsScene();
		mGraphicsViews[i]->setScene(mScenes[i]);
		mGraphicsViews[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		mGraphicsViews[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	}
    ui->cmbCameras->clear();
	mCameraCount = mUcm->initialize();
	
    for(i=0;i<mCameraCount;i++)
	{
		UsbCamera* camera = mUcm->getCameraByIndex(i);
		if (camera)
		{
			ui->cmbCameras->addItem(camera->name());
			camera->open();
		}
	}
	if (mCameraCount > 0)
	{
		on_cmbCameras_currentIndexChanged(0);
	}
	return mCameraCount > 0;
}

void MainWindow::on_cmbCameras_currentIndexChanged(int index)
{
    if(mFirstCameraChange)
    {
        mFirstCameraChange = false;
    }
    else
    {
        ////videoInput *VI = &videoInput::getInstance();
        ////CamParametrs params = VI->getParametrs(index);
        //ui->spinExposure->setMinimum(params.Exposure.Min);
        //ui->spinExposure->setMaximum(params.Exposure.Max);
        //ui->spinExposure->setValue(params.Exposure.CurrentValue);

        //ui->spinGain->setMinimum(params.Gain.Min);
        //ui->spinGain->setMaximum(params.Gain.Max);
        //ui->spinGain->setValue(params.Gain.CurrentValue);

        //ui->spinBalance->setMinimum(params.WhiteBalance.Min);
        //ui->spinBalance->setMaximum(params.WhiteBalance.Max);
        //ui->spinBalance->setValue(params.WhiteBalance.CurrentValue);
    }
}

void MainWindow::on_cmbDPI_currentIndexChanged(int index)
{
    //videoInput *VI = &videoInput::getInstance();
    //int curCamera = ui->cmbCameras->currentIndex();
    //if(VI->isDevicesAcceable())
    //{
    //    VI->setupDevice(curCamera,mWidth[index],mHeight[index]);
    //}
    //QGraphicsScene* scene = (0 == index)?mScene1:mScene2;
    //scene->setSceneRect(0,0,mWidth[index],mHeight[index]);
}

void MainWindow::on_pbExposure_clicked()
{
    //videoInput *VI = &videoInput::getInstance();
    //int curIndex = ui->cmbCameras->currentIndex();
    ////if(VI->isDevicesAcceable())
    //{
    //    CamParametrs CP = VI->getParametrs(curIndex);
    //    CP.Exposure.CurrentValue = ui->spinExposure->value();
    //    CP.Exposure.Flag = 1;
    //    VI->setParametrs(curIndex, CP);
    //}
}

void MainWindow::on_pbGain_clicked()
{
    //videoInput *VI = &videoInput::getInstance();
    //int curIndex = ui->cmbCameras->currentIndex();
    ////if(VI->isDevicesAcceable())
    //{
    //    CamParametrs CP = VI->getParametrs(curIndex);
    //    CP.Gain.CurrentValue = ui->spinGain->value();
    //    CP.Gain.Flag = 1;
    //    VI->setParametrs(curIndex, CP);
    //}
}

void MainWindow::on_pbBalance_clicked()
{
    //videoInput *VI = &videoInput::getInstance();
    //int curIndex = ui->cmbCameras->currentIndex();
    ////if(VI->isDevicesAcceable())
    //{
    //    CamParametrs CP = VI->getParametrs(curIndex);
    //    CP.WhiteBalance.CurrentValue = ui->spinBalance->value();
    //    CP.WhiteBalance.Flag = 1;
    //    VI->setParametrs(curIndex, CP);
    //}
}
//开始
void MainWindow::on_pbStart_clicked()
{
    int curDegree = 0;
    int step = ui->leAutoStep->text().toInt();
	QString qName = ui->cmbClassify->currentText();
	std::string strEnName = mClassify[qName.toStdString()];
    mDisplayCond = false;
	QThread::msleep(3000);
    int count=0;
	//while(0)
	do
    {
        //MoveTo
		mMotionCard.relMove(0, mMotionVel, mPulsePerAngle*step, true);
        for(int i=0;i<mCameraCount;i++)
        {
			QImage img;
			if (0 == getImage(i, img))
			{
				//QString qDirectory = QString("%1/snap/%2").arg(mStartup).arg(strEnName.c_str());
				QString qDirectory = getPath();
				QDir qdir;
				if (!qdir.exists(qDirectory))
				{
					qDirectory = mkMutiDir(qDirectory);
					//qdir.mkdir(qDirectory);
				}
				QString name = getName(i);
				QString sFile = QString("%1/%2").arg(qDirectory).arg(name);
				img.save(sFile, "jpg");
			}
        }
        curDegree += step;
        count++;
	} while (curDegree < 360);

	QTableWidget *tableWidget = ui->tableWidget;
	 
	
	auto RecordTabelUi = [&step, this](QTableWidget *tableWidget)
	{
		int rows = tableWidget->rowCount();
		int cols = tableWidget->columnCount();
		for (int i = 0; i < rows; i = i++ ) 
		{
			for (int j = 0; j < cols; j=j+2 ) 
			{
				
				QCheckBox *qcb = (QCheckBox*)tableWidget->cellWidget(i, j);
				if (qcb->checkState()) 
				{
					QTableWidgetItem *it = tableWidget->item(i, j + 1);		
					QString test = it->text();
					int tmp = it->text().toInt();
					tmp = tmp + (360 / step) * products[i].proNum * 3;
					QString str = QString::number(tmp);
					it->setText(str);
				}
			}
		}
	};
	QString path = mStartup + "/count.xls";
	auto RecordExcel = [path](QTableWidget *tableWidget)
	{
		ExcelEngine excel;
		if(!excel.Open(path))
		{
			return -1;
		}
		vector<vector<QString>> tableExcel;

		
		excel.ReadDataToVector(tableExcel);
		int rows = tableWidget->rowCount();
		int cols = tableWidget->columnCount();
		for(int j = 0; j < rows ; j++)
		{
			QTableWidgetItem *it = tableWidget->verticalHeaderItem(j);
			QString label = it->text();
			if(label.isEmpty())
			{
				continue;
			}
			for (int i = 1; i < tableExcel.size(); i++)
			{
				QString labelTable = tableExcel[i][0];
				if(labelTable.isEmpty())
				{
					continue;
				}
				if (label.compare(labelTable) == 0) 
				{
					for (int k = 0; k< cols; k = k + 2)
					{
						QTableWidgetItem *it = tableWidget->item(j, k+1);
						QString result = it->text();
						excel.SetCellData(i + 1, k/2 + 1 + 1, result);
					}
				}

			}
		}
		excel.Save();
		excel.Close();
	};
	

	if(products.size()!=1)
	{
		RecordTabelUi(ui->tableWidget);
		RecordExcel(ui->tableWidget);
	}
	
    mDisplayCond = true;
    QMessageBox msg;
    msg.setText("Finished");
    msg.exec();
}

void MainWindow::on_pbBrowse_clicked()
{

}
//抓拍
void MainWindow::on_pbSnap_clicked()
{
    mDisplayCond = false;
    int curIndex = ui->cmbCameras->currentIndex();
	QImage qimg;
	if (0 == getImage(curIndex, qimg))
	{
		QString sFile = QString("%1/snap/%2.jpg").arg(mStartup).arg(QDateTime::currentDateTime().toString("yy_MM_dd_HH_mm_ss"));
		qimg.save(sFile,"jpg");
		showMessage(QStringLiteral("OK"));
	}
	else
	{
		showMessage(QStringLiteral("Fail"));
	}

    mDisplayCond = true;
}

void MainWindow::on_pbRotation_clicked()
{
	int step = ui->leStep->text().toInt();
	mMotionCard.relMove(0, mMotionVel, mPulsePerAngle*step, false);
}

void MainWindow::on_pbRotation2_clicked()
{
	int step = ui->leStep->text().toInt();
	mMotionCard.relMove(0, mMotionVel, mPulsePerAngle*-1*step, false);
}

void MainWindow::on_pbGo_clicked()
{
	int pos = ui->leAbsPos->text().toInt();
	mMotionCard.absMove(0, mMotionVel, mPulsePerAngle*pos, false);
}

void MainWindow::startThread()
{
    mThreadCond = true;
    mDisplayCond = true;
	for (int i = 0; i < mCameraCount; i++)
	{
		std::thread t(displayFoo, this, i);
		t.detach();
	}
}

void MainWindow::displayFoo(MainWindow* mw, int index)
{
    mw->onDisplayFoo(index);
}

void MainWindow::onDisplay(QImage img, int index)
{
	if (0 > index || DISPLAY_CAMERA_COUNT <= index) { return; }
	QGraphicsScene* scene = mScenes[index];
    scene->clear();
	QGraphicsView* view = mGraphicsViews[index];
	int w = view->width();
	int h = view->height();
	view->setSceneRect(0, 0, w, h);
	QPixmap pixmap = QPixmap::fromImage(img).scaled(w,h);
	scene->addPixmap(pixmap);
}

int MainWindow::getImage(int index, QImage& qimg)
{
	unsigned char* img = mImages[index];
	bmImage image;
	if (0 <= index && index <= mCameraCount)
	{
		UsbCamera* camera = mUcm->getCameraByIndex(index);
		//mMutex.lock();
		QThread::msleep(300);
		try
		{
			if (0 == camera->grabOne(&image))
			{
				memcpy(img, image.data, image.w*image.h * 3);
				QImage qimg1(img, image.w, image.h, QImage::Format_RGB888);
				if (startAWB)
					awb(qimg1, index);
				qimg = qimg1;
				//mMutex.unlock();
				return 0;
			}
			QThread::msleep(300);
		}
		catch(runtime_error e)
		{
			qInstallMessageHandler(outputMessageX);
			qCritical(e.what());
		}
		//mMutex.unlock();
	}
	return -1;
}

int MainWindow::awb(QImage &qImg, int index)
{
	if (index == 0) 
	{
		mMutex[0].lock();
		RGBGain Gain;
		cv::Mat img;
		QImage2Mat(qImg, img);

		if (img.empty())
			throw runtime_error("img is empty, line 901, awb, cameraid:" + index);

		if (isOpenAWBmode) 
		{
			dwb.DynamicWB(img);
		}
		Gain = dwb.getRGBGain();


		if (img.type() == CV_8UC3)
		{
			
			vector<cv::Mat> channels(3);
			//split 导出的通道反
			cv::split(img, channels);

			channels[0] = channels[0] * Gain.BG;
			channels[1] = channels[1] * Gain.GG;
			channels[2] = channels[2] * Gain.RG;

			vector<cv::Mat> balanceRGB;
			balanceRGB.push_back(channels[0]);
			balanceRGB.push_back(channels[1]);
			balanceRGB.push_back(channels[2]);

			if (img.empty())
				throw runtime_error("img is empty, line 1048, awb, cameraid:" + index);

			cv::merge(balanceRGB, img);
			Mat2QImage(img, qImg);
		}
		else
		{
			return -1;
		}
		mMutex[0].unlock();
	}
	else if (index == 1) 
	{
		mMutex[1].lock();
		RGBGain Gain;
		cv::Mat img;
		QImage2Mat(qImg, img);


		if (isOpenAWBmode)
		{
			dwb1.DynamicWB(img);
		}
		Gain = dwb1.getRGBGain();

		if (img.type() == CV_8UC3)
		{
			vector<cv::Mat> channels(3);
			cv::split(img, channels);
			channels[0] = channels[0] * Gain.BG;
			channels[1] = channels[1] * Gain.GG;
			channels[2] = channels[2] * Gain.RG;

			vector<cv::Mat> balanceRGB;
			balanceRGB.push_back(channels[0]);
			balanceRGB.push_back(channels[1]);
			balanceRGB.push_back(channels[2]);

			if (img.empty())
				throw runtime_error("img is empty, line 1048, awb, cameraid:" + index);

			cv::merge(balanceRGB, img);
			Mat2QImage(img, qImg);
		}
		else
		{
			return -1;
		}
		mMutex[1].unlock();
	}
	else if (index == 2) 
	{
		mMutex[2].lock();
		RGBGain Gain;
		cv::Mat img;
		QImage2Mat(qImg, img);

		if (isOpenAWBmode)
		{
			dwb2.DynamicWB(img);
		}
		Gain = dwb2.getRGBGain();

		if (img.type() == CV_8UC3)
		{
			vector<cv::Mat> channels(3);
			cv::split(img, channels);
			channels[0] = channels[0] * Gain.BG;
			channels[1] = channels[1] * Gain.GG;
			channels[2] = channels[2] * Gain.RG;

			vector<cv::Mat> balanceRGB;
			balanceRGB.push_back(channels[0]);
			balanceRGB.push_back(channels[1]);
			balanceRGB.push_back(channels[2]);

			if (img.empty())
				throw runtime_error("img is empty, line 1048, awb, cameraid:" + index);

			cv::merge(balanceRGB, img);
			Mat2QImage(img, qImg);
		}
		else
		{
			return -1;
		}
		mMutex[2].unlock();
	}
	else 
	{
		return -1;
	}

	return 0;
}

int MainWindow::QImage2Mat(QImage &qImg, cv::Mat &img)
{
	//qDebug() << qImg.format();
	switch (qImg.format())
	{
	case QImage::Format::Format_ARGB32_Premultiplied:
		img = cv::Mat(qImg.height(), qImg.width(), CV_8UC4, (void*)qImg.constBits(), qImg.bytesPerLine());
		break;
	case QImage::Format::Format_RGBA8888_Premultiplied:
		img = cv::Mat(qImg.height(), qImg.width(), CV_8UC3, (void*)qImg.constBits(), qImg.bytesPerLine());
		break;
	case QImage::Format::Format_Indexed8:
		img = cv::Mat(qImg.height(), qImg.width(), CV_8UC1, (void*)qImg.constBits(), qImg.bytesPerLine());
		break;
	case QImage::Format::Format_RGB888:
		img = cv::Mat(qImg.height(), qImg.width(), CV_8UC3, (void*)qImg.bits(), qImg.bytesPerLine());
		cv::cvtColor(img, img, CV_BGR2RGB);
		break;
	default:
		return -1;
	}
	return 0;
}

int MainWindow::Mat2QImage(cv::Mat & img, QImage & qImg)
{
	if (img.type() == CV_8UC3) {
		const uchar *p = (const uchar *)img.data;
		QImage tmp = QImage(p, img.cols, img.rows, img.step, QImage::Format_RGB888);
		qImg = tmp.rgbSwapped();
		return 0;
	}
	else {
		return -1;
	}
}

QString MainWindow::getTime(QString format)
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString(format);
	return current_date;
}

QString MainWindow::genFile()
{

	return QString();
}
//path = "180512-1/ljn/zhuhe"
QString MainWindow::mkMutiDir(const QString path)
{
	QDir dir(path);
	if (dir.exists(path)){
		return path;
	}
	QString parentDir = mkMutiDir(path.mid(0, path.lastIndexOf('/')));
	QString dirname = path.mid(path.lastIndexOf('/') + 1);
	QDir parentPath(parentDir);
	if (!dirname.isEmpty())
		parentPath.mkpath(dirname);
	return parentDir + "/" + dirname;;
}

QString MainWindow::getPath()
{
	QString fpath = mStartup + "/" + pathUi.taskLineEdit->text() + "/" + pathUi.usrLineEdit->text() + "/" + pathUi.zuheLineEdit->text();
	//mfile = mkMutiDir(fpath);
	return fpath;
}

QString MainWindow::getName(int index)
{
	QString name = getTime("yyMMdd") + musrName + getTime("HHmmsszzz") + "-" + QString::number(index) + ".jpg";
	return name;
}

void MainWindow::onDisplayFoo(int index)
{
	if (0 <= index && index <= DISPLAY_CAMERA_COUNT)
	{
		QImage qimg;
		while (mThreadCond)
		{
			if (mDisplayCond)
			{
				if (0 == getImage(index, qimg))
				{
					emit displaySig(qimg, index);
				}
			}
			QThread::msleep(100);//100
		}
	}
}

void MainWindow::on_pbParamSet_clicked()
{
    //videoInput *VI = &videoInput::getInstance();
    //int curIndex = ui->cmbCameras->currentIndex();

}

void MainWindow::on_slideLight1_valueChanged(int value)
{
	mLightCtrl.setBright(0, value);
}

void MainWindow::on_slideLight2_valueChanged(int value)
{
	mLightCtrl.setBright(1, value);
}

void MainWindow::on_slideLight3_valueChanged(int value)
{
	mLightCtrl.setBright(2, value);
}

void MainWindow::on_slideLight4_valueChanged(int value)
{
	mLightCtrl.setBright(3, value);
}

void MainWindow::on_slideLight5_valueChanged(int value)
{
	mLightCtrl.setBright(4, value);
}

void MainWindow::on_slideLight6_valueChanged(int value)
{
	mLightCtrl.setBright(5, value);
}

void MainWindow::on_slideLight7_valueChanged(int value)
{
	mLightCtrl.setBright(6, value);
}

void MainWindow::on_slideLight8_valueChanged(int value)
{
	mLightCtrl.setBright(7, value);
}

