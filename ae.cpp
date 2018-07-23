#include "ae.h"

AutoExposure::AutoExposure(VideoCapture & camera, float startparamter)
{
	this->camera = camera;
	camera.set(CAP_PROP_EXPOSURE, startparamter);
	this->s_bright = startparamter;
}

AutoExposure::~AutoExposure()
{
}

bool AutoExposure::apporiateExposure(Mat & img)
{
	currentImg = img;
	return false;
}

float AutoExposure::EstimateContrast()
{
	float mean_white = getMeanBright(currentImg, whiteMask);
	float mean_black = getMeanBright(currentImg, blackMask);
	currentContrastValue = mean_white / mean_black;
	return currentContrastValue;
}

void AutoExposure::adjustExposureTime()
{
	if(lastContrastValue < currentContrastValue)
	{
		s_bright = s_bright + 0.1;
		camera.set(CAP_PROP_EXPOSURE, s_bright);
		isOkExposure = false;
	}
	else
	{
		isOkExposure = true;
	}
}

float AutoExposure::getMeanBright(Mat & img, Mat & mask)
{
	int accumulate = 0;
	int num = 0;
	for (int i = 0; i < img.rows; i++) 
	{
		for(int j = 0 ; j < img.cols; j++)
		{
			if(*mask.ptr(i,j)==255)
			{
				accumulate = accumulate + *img.ptr(i, j);
				num++;
			}
		}
	}
	return accumulate / num;
}

void AutoExposure::getMask()
{
	Mat imgWhite;
	Mat imgBlack;
	adaptiveThreshold(currentImg, imgWhite, 255, THRESH_BINARY, BORDER_REPLICATE, 5, 0);
	adaptiveThreshold(currentImg, imgBlack, 255, THRESH_BINARY_INV, BORDER_REPLICATE, 5, 0);

	Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));
	morphologyEx(imgWhite, whiteMask, MORPH_CLOSE, element);
	morphologyEx(imgBlack, blackMask, MORPH_CLOSE, element);
}
