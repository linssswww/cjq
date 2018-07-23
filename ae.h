#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
using namespace cv;
class AutoExposure
{
public:
	AutoExposure(VideoCapture &camera, float startExposure);
	~AutoExposure();
public:
	bool apporiateExposure(Mat &img);
private:
	float EstimateContrast();
	void adjustExposureTime();
	float getMeanBright(Mat &img, Mat &mask);
	void getMask();
	float lastContrastValue;
	float currentContrastValue;

	float blackRegionValue;
	float blackWhiteValue;

	Mat blackMask;
	Mat whiteMask;

	Mat currentImg;

	float s_bright;
	VideoCapture camera;

	bool isOkExposure;
};