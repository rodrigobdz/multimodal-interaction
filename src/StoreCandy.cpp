#include "StoreCandy.h"

using namespace std;
using namespace cv;

cStoreCandy::cStoreCandy()
{
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
	int nTrialsX = 5;
	int nTrialsY = 5;
	
	int nStepX = nWidth/nTrialsX;
	int nStepY = nHeight/nTrialsY;

	Point pntCurrent;
	
	for(size_t i=1; i <= nTrialsX; i++)
	{
		for(size_t j=1; j <= nTrialsY; j++)
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
	for(size_t i=0; i<moCurrentCandy.size(); i++)
	{
		int nDesign = moCurrentCandy.at(i).nDesign;
		Point nPosition = moCurrentCandy.at(i).pntPosition;
		
		// moAvailableCandy.at(nDesign).copyTo(/*Do sth. here*/);
	}
	
	
	return 0;
}
