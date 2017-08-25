#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp> 
#include<iostream>
using namespace std;
using namespace cv;

void drawCornerOnImage(Mat& image, const Mat&binary)
{
	Mat_<uchar>::const_iterator it = binary.begin<uchar>();
	Mat_<uchar>::const_iterator itd = binary.end<uchar>();
	for (int i = 0; it != itd; it++, i++)
	{
		if (*it)
			circle(image, Point(i%image.cols, i / image.cols), 10, Scalar(0, 255, 0), 1);
	}
}
int main_3_4()
{
	//使用灰度图读入 Mat image = imread("C:\\Users\\lejia\\Desktop\\opencv\\pic\\10.png",0);
	Mat image = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	Mat gray;
	cvtColor(image, gray, CV_BGR2GRAY);

	//找出角点
	Mat cornerStrength;
	cornerHarris(gray, cornerStrength, 3, 3, 0.01);

	double maxStrength;
	double minStrength;
	//找到角点图像中的最大、最小值
	minMaxLoc(cornerStrength, &minStrength, &maxStrength);

	Mat dilated;
	Mat locaMax;

	// cornerstrength膨胀处理输出到dilated
	dilate(cornerStrength, dilated, Mat());

	//返回两幅图像中对应点相同的二值图像
	compare(cornerStrength, dilated, locaMax, CMP_EQ);

	Mat cornerMap;
	double qualityLevel = 0.01;
	double th = qualityLevel*maxStrength;
	//阈值计算:qualitylevel*图像中的最大值（角点的最大颜色）
	threshold(cornerStrength, cornerMap, th, 255, THRESH_BINARY);
	cornerMap.convertTo(cornerMap, CV_8U);

	// 逐点的位运算，使每个角点都只占有一个点
	bitwise_and(cornerMap, locaMax, cornerMap);
	imshow("二值图", cornerMap);
	drawCornerOnImage(image, cornerMap);
	namedWindow("result");
	imshow("result", image);
	waitKey();

	return 0;
}