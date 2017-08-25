#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat tmp = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png", 1);
	imshow("show pictur", tmp);
	int param = 50;
	for (int i = 0; i<tmp.rows; i++)
		for (int j = 0; j<tmp.cols; j++)
		{
			tmp.at<Vec3b>(i, j)[0] = tmp.at<Vec3b>(i, j)[0] / param*param;
			tmp.at<Vec3b>(i, j)[1] = tmp.at<Vec3b>(i, j)[1] / param*param;
			tmp.at<Vec3b>(i, j)[2] = tmp.at<Vec3b>(i, j)[2] / param*param;
		}
	imshow("show picture1", tmp);
	waitKey(0);
	return 0;
}