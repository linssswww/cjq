#ifndef DWB_H
#define DWB_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#define IMGWIDTH 1600
#define IMGHEIGHT 1200

using namespace std;
struct RGBGain
{
    float RG;
    float GG;
    float BG;
};

class DWB
{
private:
    cv::Mat src; //输入图像
	cv::Mat CbPlot, CrPlot; //CB、CR图像分块信息
	cv::Mat R, G, B, Y, Cr, Cb; //图像在两个空间的六个通道
	cv::Mat DistinguishY;
    vector<cv::Mat> RGBChannels; //图像R G B通道
    vector<cv::Mat> YCbCrChannels; //图像Y Cb Cr通道
    vector<cv::Mat> vCbPlot, vCrPlot; //存放各CbPlot、CrPlot的分块图像信息
    vector<float> vMb, vMr, vDb, vDr; //存放各块的4个统计值
    vector<float> WhitePointY; //存放参考白点的Y值
    vector<int> PreserveNO; //存放满足阈值选择的块编号
    vector<cv::Point> WhitePointSet;
	cv::Point WhitePoint;//存放可能的白色点坐标，并存于WhitePointSet中
    float Mb, Mr, Db, Dr;
    int IMGRows, IMGCols, N;
    RGBGain Gain;
    int sign(float input); //符号函数
	cv::Point WhitePointPositionIncrement(int input); //参考白点偏移增量计算公式
    void RGB2YCrCb(cv::Mat MR, cv::Mat MG, cv::Mat MB, cv::Mat MY, cv::Mat MCr, cv::Mat MCb); //颜色通道转换公式
    void SizeAdjust();
	


public:
	void VideoCapture();
    int SpaceChange(cv::Mat Input); //① 将图像从RGB空间变换到YCrCb空间
    int CRCBBlocking(); //② Cr、Cb图像分块 分成4*4块 存放在VCRPlot 和 VCBPlot中
    int ParaCal(); //③ 计算每块的Mr、Mb、Dr、Db的四个参数
    int WhiteRigionSel();
    int Distinguish();
    void GetGain();
    RGBGain DynamicWB(cv::Mat InputIMG);
    RGBGain operator=(const RGBGain &R) const;
	RGBGain getRGBGain();
	int ClearAll();
	int threshImgSelectWhite(vector<cv::Mat> &vecWhite, cv::Mat &img);
};

#endif // DWB_H
