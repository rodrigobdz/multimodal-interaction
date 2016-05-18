#pragma once

#include <iostream>
#include "opencv2/opencv.hpp"

class cStoreCandy
{
private:

	std::vector<cv::Mat> moAvailableCandy;
	
	struct sCandys
	{
		cv::Point pntPosition;
		int nDesign;
	};
	
	std::vector<sCandys> moCurrentCandy;
	std::vector<cv::Point> moGrid;

public:

	cStoreCandy();
	~cStoreCandy();

	int initialize(std::vector<cv::Mat> oAvailableCandy, int nWidth, int nHeight);
	int setUpCandy();
	int checkCollision(cv::Rect rctFacePosition);
	int plotCandy(cv::Mat * oImg);
	
};