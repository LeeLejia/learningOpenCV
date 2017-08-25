#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main_1_3()
{
	Mat orign = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	imshow("orign", orign);
	Mat tmp = orign(Range(orign.rows/4,orign.rows/2),Range(0, orign.cols / 2));
	imshow("tmp", tmp);
	waitKey(0);
	return 0;
}

//²âÊÔ£ºÊÇ·ñ¹²ÏíÄÚ´æ£¿