#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int pic_width = 250;
int pic_height = 250;
Mat pic;
Mat tmp_blur;
Mat tmp_gaussianblur;

int sigma = 1;
int kernel = 1;
void valuechange(int, void*)
{
	//核大小须为偶数
	kernel = kernel & 1 ? kernel : kernel + 1;
	//均值滤波函数：输入图，输出图，核大小
	blur(pic, tmp_blur, Size(kernel, kernel), Point(-1, -1), BORDER_DEFAULT);
	//高斯模糊
	GaussianBlur(pic, tmp_gaussianblur, Size(kernel, kernel), (double)sigma / 10, (double)sigma / 100, BORDER_DEFAULT);//高斯滤波函数
	imshow("原图", pic);
	imshow("模糊处理", tmp_blur);
	imshow("高斯模糊", tmp_gaussianblur);
}
int main_3_1_()
{
	pic = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	imshow("原图", pic);
	createTrackbar("核大小", "原图", &kernel, 100, valuechange);
	createTrackbar("高斯sigma：", "原图", &sigma, 100, valuechange);
	valuechange(NULL,NULL);
	waitKey(0);
	return 0;
}