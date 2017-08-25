#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main_()
{
	Mat pic_2 = imread("C:\\Users\\lejia\\Desktop\\pic\\2.jpeg")(Range(0, 200), Range(0, 200));
	Mat pic_1 = imread("C:\\Users\\lejia\\Desktop\\pic\\3.jpeg")(Range(0, 200), Range(0, 200));

	Mat pic = Mat(200, 200, 1);
	float alpha = 0.5;
	addWeighted(pic_2, alpha, pic_1, 1 - alpha, 1, pic);
	
	imshow("1", pic_1);
	imshow("2", pic_2);
	imshow("3", pic);
	waitKey(0);
	return 0;
}