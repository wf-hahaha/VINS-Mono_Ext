/*
    Dec. 2 2017, He Zhang, hxzhang1@ualr.edu 

    keyframe structure 
    
*/

#include "keyframe.h"
#include "../freak/freak.h"
#include "../freak/hammingseg.h"
#include <opencv2/legacy/legacy.hpp>
#include <iostream>
#include <fstream>

using namespace std;

CKeyFrame::CKeyFrame(): 
mbDiscribed(false)
{}
CKeyFrame::~CKeyFrame(){}

void CKeyFrame::describe(cv::Mat& img, vector<cv::KeyPoint>& kpts, cv::Mat& desc)
{
    cv_ext::FREAK extractor; 
    // extractor.compute(mImg, mvKPts, mDiscriptor); 
    desc = cv::Mat(); 
    extractor.compute(img, kpts, desc); 
    return ;
}

void CKeyFrame::describe()
{
    if(mbDiscribed) return; 
    vector<cv::KeyPoint> tmpPts = mvKPts; 
    describe(mImg, tmpPts, mDiscriptor); 
    mDes2Id.resize(mDiscriptor.rows); 
    for(int i=0; i<mDes2Id.size(); i++)
    {
	cv::KeyPoint& p1 = tmpPts[i];
	int j = 0;
	for(; j<mIds.size(); j++)
	{
	    cv::KeyPoint& p2 = mvKPts[j];
	    // if(fabs(p1.pt.x - p2.pt.x) < 0.1 && fabs(p1.pt.y - p2.pt.y) < 0.1)
	    if(p1.pt.x == p2.pt.x && p1.pt.y == p2.pt.y)
	    {
		mDes2Id[i] = j; // map the Desc' index to Id's index
		break;
	    }
	}
	if(j >= mIds.size())
	{
	    cerr <<"i = "<<i<<" p1.x = "<<p1.pt.x<<" p1.y = "<<p1.pt.y<<endl;
	    cerr <<"keyframe: j = "<<j<<" > mIds.size() = "<<mIds.size()<<endl; 
	}
    }
//    ofstream fpts1("before_describe.log"); 
//    ofstream fpts2("after_describe.log");
//    for(int i=0; i<mvKPts.size(); i++)
//    {
//	  cv::KeyPoint& p1 = mvKPts[i];
//	  fpts1<<p1.pt.x<<" "<<p1.pt.y<<endl;
//    }
//    for(int i=0; i<tmpPts.size(); i++)
//    {
//	 cv::KeyPoint& p1 = tmpPts[i]; 
//	 fpts2<<p1.pt.x<<" "<<p1.pt.y<<endl;
//    }
//	
    mbDiscribed = true; 
    return ; 
}
