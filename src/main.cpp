#include <iostream>
#include <opencv2\opencv.hpp>
#include <irrKlang.h>
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
	CandyImgs.push_back(cv::imread("candy1.png", -1)); // Caution!! read with -1 flag to get alpha channel
	CandyImgs.push_back(cv::imread("candy2.png", -1));
	CandyImgs.push_back(cv::imread("candy3.png", -1));
	
	cv::Mat initImg;
	camera >> initImg;

	if (Candys.initialize(CandyImgs,initImg.cols,initImg.rows) < 0)
	{
		std::cout << "FATAL Can't create Candys.. STOP" << std::endl;
		return -1;
	}
	Candys.setUpCandy(cv::Rect(1, 1, 1, 1));

	cv::namedWindow(WINDOW_NAME, cv::WINDOW_KEEPRATIO | cv::WINDOW_AUTOSIZE);

	// TODO Replace by our tracking
	VideoFaceDetector detector(CASCADE_FILE, camera);
	cv::Mat frame;

	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	engine->play2D("getout.ogg", true);

	while (true)
	{
		// TODO Replace by our tracking
		detector >> frame;
		cv::rectangle(frame, detector.face(), cv::Scalar(255, 0, 0));
		cv::circle(frame, detector.facePosition(), 30, cv::Scalar(0, 255, 0));

		// brief: predicted mouth area
		// TODO replace this
		cv::Rect mth;
		mth.x = detector.face().x + (int)((double)detector.face().width / 4);
		mth.y = detector.face().y + (int)(2 * (double)detector.face().height / 3);
		mth.height = (int)((double)detector.face().height / 4);
		mth.width = (int)((double)detector.face().width / 2);
		cv::rectangle(frame, mth, cv::Scalar(255, 0, 0));

		if (Candys.checkCollision(mth))
		{
			engine->play2D("explosion.wav");
		}
		Candys.plotCandy(&frame);

		/*
		cv::Mat flipped = cv::Mat(frame.rows, frame.cols, CV_8UC3);
		cv::flip(frame, flipped, 1);
		frame = flipped;
		*/

		cv::imshow(WINDOW_NAME, frame);
		if (cv::waitKey(25) == 27) break;
	}

	engine->drop();
	return 0;
}