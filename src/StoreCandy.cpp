#include "StoreCandy.h"

using namespace std;
using namespace cv;

cStoreCandy::cStoreCandy()
{
	mnScore = 0;
	mdTimerStart = (double)getTickCount();
	mdLastChange = 0;
	mnCurPos = 0;
}

cStoreCandy::~cStoreCandy()
{
}

int cStoreCandy::initialize(std::vector<cv::Mat> oAvailableCandy, int nWidth, int nHeight)
{
	if( (oAvailableCandy.size() <= 0) ||
		(nWidth < 30) ||
		(nHeight < 30) )
	{
		cout << "Bad Initialzation of Store Candy Class STOP" << endl;
		return -1;
	}
	
	// Set Up Candys
	moAvailableCandy = oAvailableCandy;
	
	// Compute Grid
	int nTrialsX = 7;
	int nTrialsY = 7;
	
	int nStepX = nWidth/nTrialsX;
	int nStepY = nHeight/nTrialsY;

	Point pntCurrent;
	
	for(size_t i=1; i < nTrialsX; i++)
	{
		for(size_t j=1; j < nTrialsY; j++)
		{
			pntCurrent.x = i*nStepX;
			pntCurrent.y = j*nStepY;
			
			moGrid.push_back(pntCurrent);
		}
	}

	return 0;	
}

int cStoreCandy::setUpCandy()
{
	if(moCurrentCandy.size() >= 10)
	{
		cout << "Already enough Candy out there.. Doing Nothing" << endl;
		return -1;
	}
	
	Point pntPosition;
	
	// TODO Add some probability stuff to get positioning point
	//pntPosition = moGrid.at(1);
	
	// TODO make this more dynamic
	//moCurrentCandy.push_back();
	
	return 0;
}

int cStoreCandy::checkCollision(cv::Rect rctFacePosition)
{
	// TODO Write some code here
	
	return 0;
}

int cStoreCandy::plotCandy(cv::Mat * oImg)
{	
	double end = (double)cv::getTickCount();
	double seconds = (end - mdTimerStart) / cv::getTickFrequency();

	if ((mdLastChange + 5.0) < seconds)
	{
		mdLastChange = seconds;
		std::random_device rd;
		std::default_random_engine posGenerator(rd());
		std::uniform_int_distribution<int> distr(1, 36);
		mnCurPos = distr(posGenerator);
	}

	for (size_t i = 0; i < moGrid.size(); i++)
	{
		if (i == mnCurPos)
		{
			cv::circle(*oImg, moGrid.at(i), 10, cv::Scalar(0, 0, 255));
		}
		else
		{
			cv::circle(*oImg, moGrid.at(i), 10, cv::Scalar(255, 255, 255));
		}
	}

	char mcTxtScore[50];
	sprintf(mcTxtScore, "You ate: %i Seconds since birth: %.2lf: ", mnScore, seconds);
	cv::Point pnt;
	pnt.x = 20;
	pnt.y = 20;

	putText(*oImg, mcTxtScore, pnt, FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 0, 0),2);

	return 0;
}
