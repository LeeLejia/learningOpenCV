#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
using namespace cv;

int BlockSize = 2;
int kSize = 3;
int k = 1;//初始为0.01
Mat SrcImage, cornerStrength;
void trackevent(int, void *)
{
	//用harris算法获取角点
	cornerHarris(SrcImage, cornerStrength, BlockSize<=0?1:BlockSize, kSize, (double)k / 100);
	
	//对灰度图进行阈值操作，得到二值图并显示  
	Mat harrisCorner;
	threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);
	imshow("效果图", harrisCorner);
}
int main_3_4_1()
{
	//以灰度模式载入图像并显示
	SrcImage = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png", 0);
	imshow("原始图", SrcImage);
	namedWindow("效果图");
	createTrackbar("blockSize:", "效果图", &BlockSize, 100, trackevent);
	createTrackbar("kSize:", "效果图", &kSize, 100, trackevent);
	createTrackbar("k:", "效果图", &k, 100, trackevent);
	waitKey(0);
	return 0;
}