//#include<opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//int main_3_2()
//{
//	Mat a = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
//	imshow("原图", a);
//	cvtColor(a, a, CV_RGB2GRAY);     //转为灰度图
//	Mat ax, ay;
//	Mat axx, ayy;
//	Sobel(a, ax, CV_16S, 1, 0, -1);
//	Sobel(a, ay, CV_16S, 0, 1, -1);
//	convertScaleAbs(ax, axx);      //将CV_16S转为CV_8U
//	convertScaleAbs(ay, ayy);
//	addWeighted(axx, 0.5, ayy, 0.5, 0, a);     //将两图相加
//	imshow("效果图1", axx);
//	imshow("效果图2", ayy);
//	imshow("效果图3", a);
//	cvWaitKey(10000);
//	return 1;
//}

#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
Mat srcImage;
Mat srcImage1;
int value = 3;

Mat dstImage, edge, grayImage;

void handleEdge(int, void*)
{
	value = (value <1 ? 1 : value);
	//3x3内核来降噪(均值滤波)
	blur(grayImage, edge, Size(value, value));
	imshow("edge",edge);
	//Canny算子
	//在OpenCV2中可用，OpenCV3中已失效
	//高阶的canny用法:
	//转灰度图,降噪,canny,将得到的边缘作为掩码，拷贝原图到效果图上，得到彩色的边缘图
	Canny(edge, edge, 3, 9, 3);
	dstImage = Scalar::all(255);
	//使用边缘图作为掩码进行拷贝，即只拷贝edge的轨迹，其它位置不处理
	srcImage1.copyTo(dstImage, edge);
	imshow("效果图", dstImage);
}
int main_3_2()
{
	//载入原始图  
	srcImage = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	srcImage1 = srcImage.clone();
	//将原图像转换为灰度图像
	cvtColor(srcImage1, grayImage, COLOR_BGR2GRAY);
	dstImage.create(srcImage1.size(), srcImage1.type());
	//显示原始图 
	imshow("原图", srcImage);
	namedWindow("效果图");
	createTrackbar("kernel Size:", "效果图", &value, 100, handleEdge);
	waitKey(0);
	return 0;
}