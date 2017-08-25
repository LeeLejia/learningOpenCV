#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <string.h>
#include <opencv/cv.h>
#include <stdio.h>
using namespace cv;
using namespace std;
int main_2_3()
{
	//载入原图   
	Mat image = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	//显示原图  
	imshow("【原图】", image);
	//获取自定义核  
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out_erode,out_dilate;
	//进行腐蚀操作  
	erode(image, out_erode, element);
	//进行膨胀操作  
	dilate(image, out_dilate, element);
	//显示效果图  
	imshow("【腐蚀操作】", out_erode);
	imshow("【膨胀操作】", out_dilate);
	cvWaitKey(0);
	return 0;
}