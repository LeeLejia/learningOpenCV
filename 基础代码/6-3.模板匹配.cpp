#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
int main_6_3() {
	IplImage* imgSrc = cvLoadImage("C:\\Users\\lejia\\Desktop\\pic\\Transform.png");
	IplImage* imgTemp = cvLoadImage("C:\\Users\\lejia\\Desktop\\pic\\tmp.png");
	CvSize sizeSrc = cvGetSize(imgSrc);
	CvSize sizeTemp = cvGetSize(imgTemp);
	CvSize sizeResult = cvSize(sizeSrc.width - sizeTemp.width + 1, sizeSrc.height - sizeTemp.height + 1);
	IplImage* imgResult = cvCreateImage(sizeResult, IPL_DEPTH_32F, 1);
	cvMatchTemplate(imgSrc, imgTemp, imgResult, CV_TM_CCORR_NORMED);
	cvShowImage("MatchResult",imgResult);
	double dMax = 0.0,dMin=0.0;
	CvPoint pmax,pmin;
	//找出图像中极大极小值，及位置
	cvMinMaxLoc(imgResult,&dMin,&dMax,&pmin,&pmax);
	cout << "max:" <<dMax<<" min:"<< dMin<< endl;
	CvPoint point2 = cvPoint(pmax.x + sizeTemp.width, pmax.y + sizeTemp.height); //对角位置 
	cvRectangle(imgSrc, pmax, point2, cvScalar(255));
	cvShowImage("Find", imgSrc);
	cvWaitKey(0);
	return 0;
}

/*
	void cvMatchTemplate( 
						const CvArr* image, //输入图片，单通道、8-比特或32-比特 浮点数图像
						const CvArr* templ, //模板图片，尺寸不能大于输入图片，且与输入图片有相同的数据类型
						CvArr* result,		//比较结果的映射图片，单通道、32-比特浮点数
											  尺寸计算：如果image尺寸是 W×H，templ尺寸是 w×h ，则 result 尺寸为(W-w+1）×(H-h+1）
						int method			//指定匹配方法：与函数 cvCalcBackProjectPatch 类似。
											  它滑动过整个图像 image, 用指定方法比较 templ 与图像尺寸为 w×h 的重叠区域，并将比较结果存到 result 中。
											  函数完成比较后，通过使用cvMinMaxLoc找全局最小值CV_TM_SQDIFF*) 
											  或者最大值 (CV_TM_CCORR* and CV_TM_CCOEFF*)。
						);
	
*/