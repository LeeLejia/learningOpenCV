//图像二值化处理及对比
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <iostream>
using namespace std;

int static_binaryzation(cv::String path);
int adpt_binaryzation(cv::String path);

int main_2_2()
{
	adpt_binaryzation("C:\\Users\\lejia\\Desktop\\opencv学习\\pic\\1.png");
	cvWaitKey(0);
	return 0;
}
// 手动输入阈值
// 灰度转换  
cv::Mat s_srcGray;
cv::Mat s_dstImage;
const int s_maxVal = 255;
int s_threshold = 150;
void callback(int value, void * s) 
{
	// 根据阈值处理图像 
	cv::threshold(s_srcGray, s_dstImage,
		s_threshold, s_maxVal, cv::THRESH_BINARY);
	cv::imshow("static_dst", s_dstImage);
	cv::waitKey(0);
}

int static_binaryzation(cv::String path) {
	cv::Mat srcImage = cv::imread(path);
	if (!srcImage.data)
		return 1;
	cv::namedWindow("static_dst");
	cv::createTrackbar("threshold", "static_dst", &s_threshold, 255, callback);
	cv::cvtColor(srcImage, s_srcGray, CV_RGB2GRAY);
	srcImage.release();
	cv::imshow("static_src", s_srcGray);
}
//自适应阈值
cv::Mat image;
cv::Mat global;
int th = 100;
int blockSize = 25;
int constValue = 10;
cv::Mat local;
void callback_(int value, void * s) 
{
	// 全局二值化  
	cv::threshold(image, global, th, 255, CV_THRESH_BINARY_INV);
	// 局部二值化  
	cv::adaptiveThreshold(image, local, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);
	cv::imshow("adpt_globalThreshold", global);
	cv::imshow("adpt_localThreshold", local);
}
int adpt_binaryzation(cv::String path)
{
	cv::Mat srcImage = cv::imread(path);
	if (srcImage.empty())
	{
		cout << "read image failure" << std::endl;
		return -1;
	}
	cv::cvtColor(srcImage, image, CV_RGB2GRAY);
	srcImage.release();
	cv::imshow("adpt_src",image);
	cv::createTrackbar("threshold", "adpt_src", &th, 255, callback_);
	cv::createTrackbar("blockSize", "adpt_src", &blockSize, image.size().width>image.size().height? image.size().height : image.size().width, callback_);
	cv::createTrackbar("constValue", "adpt_src", &constValue, 255, callback_);
	cv::waitKey(0);
	return 0;
}