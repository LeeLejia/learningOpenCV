#ifdef _CH_  
#pragma package <opencv>  
#endif
#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "opencv2/core/core.hpp"                                                                                                     
#include "opencv2/video/background_segm.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/legacy/legacy.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
using namespace cv;  
using namespace std;
       
int main(int argc, char** argv){
	Mat frame, fgmask, segm, find_circle;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	Ptr<BackgroundSubtractorGMG> fgbg = Algorithm::create<BackgroundSubtractorGMG>("BackgroundSubtractor.GMG");
	if (fgbg.empty()){
		std::cerr << "Failed to create BackgroundSubtractor.GMG Algorithm." << std::endl;
		return -1;
	}

	fgbg->set("initializationFrames", 20);
	fgbg->set("decisionThreshold", 0.7);

	VideoCapture cap(0);  
	if(!cap.isOpened())  
	{  
		return -1;  
	}  
	namedWindow("FG Segmentation", WINDOW_NORMAL);
	for (;;){
		if (!cap.read(frame)){
			break;
		}

		(*fgbg)(frame, fgmask);

		frame.copyTo(segm);
		IplImage ImaskCodeBook = fgmask;
		cvSegmentFGMask(&ImaskCodeBook);
		fgmask.copyTo(find_circle);

		findContours(find_circle, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
		vector<vector<Point> > contours_poly( contours.size());
		vector<Point2f>center( contours.size());
		vector<float>radius( contours.size());
		for( int i = 0; i < contours.size(); i++){
			approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true);
			minEnclosingCircle( contours_poly[i], center[i], radius[i]);
		}
		for(int i = 0; i< contours.size(); i++ ){
			circle(segm, center[i], (int)radius[i], Scalar(100, 100, 0), 2, 8, 0);	
		}

		imshow("FG Segmentation", segm);
		imshow("mask", fgmask);

		int c = waitKey(30);
		if (c == 'q' || c == 'Q' || (c & 255) == 27)
			break;
	}

	return 0;
}