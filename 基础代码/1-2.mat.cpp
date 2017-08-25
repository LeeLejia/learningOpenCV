#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main_1_2(int argc, char **argv)
{
	Mat tmp(500, 500, CV_8UC3, Scalar(0, 0, 0));
	for (int i = 0; i<tmp.rows; i++)
		for (int j = 0; j<tmp.cols; j++)
		{
			if (i % 10 == 0 && j % 10 == 0) {
				tmp.at<Vec3b>(i, j)[0] =0;
				tmp.at<Vec3b>(i, j)[1] =255;
				tmp.at<Vec3b>(i, j)[2] =0;
			}
		}
	imshow("tmp", tmp);
	waitKey(0);
	return 0;

}

//测试：加载一张图片，并让它反色显示