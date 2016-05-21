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

int cStoreCandy::setUpCandy(cv::Rect rctFacePosition)
{
	if(moCurrentCandy.size() >= 10)
	{
		cout << "Already enough Candy out there.. Doing Nothing" << endl;
		return -1;
	}
	
	std::random_device rd;
	std::default_random_engine posGenerator(rd());
	std::uniform_int_distribution<int> distr(1, 35);
	int curPos = distr(posGenerator);
	
	
	if (rctFacePosition.x < moGrid.at(curPos).x + 10 &&
		rctFacePosition.x + rctFacePosition.width > moGrid.at(curPos).x &&
		rctFacePosition.y < moGrid.at(curPos).y + 10 &&
		rctFacePosition.height + rctFacePosition.y > moGrid.at(curPos).y)
	{
		// FIXME distribute positions in this case more dynamik
		curPos++;
		if (curPos > 35) curPos = 0;
	}
	
	sCandys candy;
	candy.rctPosition = Rect(moGrid.at(curPos).x - 10, moGrid.at(curPos).y - 10, 20, 20);

	// FIXME Add more possible designes
	candy.nDesign = 0;
	moCurrentCandy.push_back(candy);
	
	return 0;
}

int cStoreCandy::checkCollision(cv::Rect rctFacePosition)
{
	// cout << moCurrentCandy.size() << endl;
	for (size_t i = 0; i < moCurrentCandy.size(); i++)
	{
		Rect candy = moCurrentCandy.at(i).rctPosition;

		if (rctFacePosition.x < candy.x + candy.width &&
			rctFacePosition.x + rctFacePosition.width > candy.x &&
			rctFacePosition.y < candy.y + candy.height &&
			rctFacePosition.height + rctFacePosition.y > candy.y)
		{
			mnScore++;
			mnCurPos = -1;
			moCurrentCandy.erase(moCurrentCandy.begin() + i);
			setUpCandy(rctFacePosition);
		}
	}

	return 0;
}

int cStoreCandy::plotCandy(cv::Mat * oImg)
{	
	double end = (double)cv::getTickCount();
	double seconds = (end - mdTimerStart) / cv::getTickFrequency();

	
	if ((mdLastChange + 5.0) < seconds)
	{
		setUpCandy(Rect(1,1,1,1));
		mdLastChange = seconds;
	}
	

	for (size_t i = 0; i < moCurrentCandy.size();i++)
	{
		// TODO Replace by Candy Image
		// cv::rectangle(*oImg, Rect(moCurrentCandy.at(i).pntPosition.x - 10, moCurrentCandy.at(i).pntPosition.y - 10, 20, 20), cv::Scalar(0, 0255), CV_FILLED);
		//cv::rectangle(*oImg, moCurrentCandy.at(i).rctPosition, cv::Scalar(0, 0255), CV_FILLED);
		moAvailableCandy.at(moCurrentCandy.at(i).nDesign).copyTo((*oImg)(Rect(moCurrentCandy.at(i).rctPosition.x, moCurrentCandy.at(i).rctPosition.y, moAvailableCandy.at(moCurrentCandy.at(i).nDesign).cols, moAvailableCandy.at(moCurrentCandy.at(i).nDesign).rows)));
	}

	/*
	for (size_t i = 0; i < moGrid.size(); i++)
	{
		cv::circle(*oImg, moGrid.at(i), 10, cv::Scalar(255, 255, 255));
	}
	*/
	char mcTxtScore[50];
	sprintf(mcTxtScore, "You ate: %i Seconds since birth: %.2lf: ", mnScore, seconds);
	cv::Point pnt;
	pnt.x = 20;
	pnt.y = 20;

	putText(*oImg, mcTxtScore, pnt, FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 0, 0),2);

	return 0;
}
