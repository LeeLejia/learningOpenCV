#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <stdio.h>
using namespace cv;
using namespace std;
int main()
{
	//载入原始图    
	Mat image = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	//显示原始图   
	imshow("【原始图】", image);
	//定义核  
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行形态学操作  
	Mat open, close;
	//开运算
	morphologyEx(image, open, MORPH_OPEN, element);
	//闭运算
	morphologyEx(image, close, MORPH_CLOSE, element);
	//显示效果图   
	imshow("【开运算】", open);
	imshow("【闭运算】", close);
	waitKey(0);

	return 0;
}
