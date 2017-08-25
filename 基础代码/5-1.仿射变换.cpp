#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>  
using namespace cv;
using namespace std;
int main_5_1()
{
	//数组声明
	CvPoint2D32f srcTri[3], dstTri[3];
	//创建指针
	CvMat* warp_mat = cvCreateMat(2, 3, CV_32FC1);
	CvMat* rot_mat = cvCreateMat(2, 3, CV_32FC1);
	//载入和显示图像
	IplImage *src;
	src = cvLoadImage("C:\\Users\\lejia\\Desktop\\pic\\1.png", CV_LOAD_IMAGE_UNCHANGED);
	cvNamedWindow("原图", CV_WINDOW_AUTOSIZE);
	cvShowImage("原图", src);

	IplImage *dst = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	dst = cvCloneImage(src);

	dst->origin = src->origin;
	cvZero(dst);
	//方法1：
	//分别指定源矩阵和目标矩阵的3个点
	srcTri[0].x = 0;
	srcTri[0].y = 0;
	srcTri[1].x = src->width;
	srcTri[1].y = 0;
	srcTri[2].x = 0;
	srcTri[2].y = src->height;

	dstTri[0].x = 10;
	dstTri[0].y = 10;
	dstTri[1].x = 200;
	dstTri[1].y = 50;
	dstTri[2].x = 60;
	dstTri[2].y =250;
	//使用定义的点计算出仿射参数矩阵
	cvGetAffineTransform(srcTri, dstTri, warp_mat);
	//cvPerspectiveTransform(srcTri, dstTri, warp_mat);
	//对矩阵进行仿射变换
	cvWarpAffine(src, dst, warp_mat);
	cvNamedWindow("仿射图1", CV_WINDOW_AUTOSIZE);
	cvShowImage("仿射图1", dst);
	cvSaveImage("C:\\Users\\lejia\\Desktop\\pic\\Transform.png", dst);
	//方法2：
	CvPoint2D32f center = cvPoint2D32f(src->width / 2, src->height / 3);//定义中心点
	double angle = -50.0;//旋转角度
	double scale = 0.5;//放缩比例，正负号效果相当于旋转180度
	//计算得到包含旋转缩放变换的仿射参数矩阵
	cv2DRotationMatrix(center, angle, scale, rot_mat);
	//对矩阵进行仿射变换
	cvWarpAffine(src, dst, rot_mat);
	Mat t;  //变换矩阵  
	cvNamedWindow("仿射图2", CV_WINDOW_AUTOSIZE);
	cvShowImage("仿射图2", dst);

	cvWaitKey();
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvDestroyWindow("原图");
	cvDestroyWindow("仿射图1");
	cvDestroyWindow("仿射图2");
	cvReleaseMat(&rot_mat);
	cvReleaseMat(&warp_mat);
	return 0;


}