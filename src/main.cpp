#include <iostream>
#include <opencv2\opencv.hpp>
#include "face_detect_n_track\VideoFaceDetector.h"
#include "StoreCandy.h"

const cv::String    WINDOW_NAME("Camera video");
const cv::String    CASCADE_FILE("haarcascade_frontalface_default.xml");

int main(int argc, char** argv)
{
	// open the cam
	cv::VideoCapture camera(0);
	if (!camera.isOpened()) 
	{
		std::cout << "FATAL Can't open Camera.. STOP" << std::endl;
		return -1;
	}

	cStoreCandy Candys;
	std::vector<cv::Mat> CandyImgs;
	CandyImgs.push_back(cv::imread("..\\..\\img\\candy_icon.png"));
	cv::Mat initImg;
	camera >> initImg;

	if (Candys.initialize(CandyImgs,initImg.cols,initImg.rows) < 0)
	{
		std::cout << "FATAL Can't create Candys.. STOP" << std::endl;
		return -1;
	}

	cv::namedWindow(WINDOW_NAME, cv::WINDOW_KEEPRATIO | cv::WINDOW_AUTOSIZE);

	// TODO Replace by our tracking
	VideoFaceDetector detector(CASCADE_FILE, camera);
	cv::Mat frame;

	// TODO add some Musik

	while (true)
	{
		// TODO Replace by our tracking
		detector >> frame;
		cv::rectangle(frame, detector.face(), cv::Scalar(255, 0, 0));
		cv::circle(frame, detector.facePosition(), 30, cv::Scalar(0, 255, 0));

		// TODO implement collisionfunction of cStoreCandy
		Candys.plotCandy(&frame);
	
		cv::imshow(WINDOW_NAME, frame);
		if (cv::waitKey(25) == 27) break;
	}

	return 0;
}