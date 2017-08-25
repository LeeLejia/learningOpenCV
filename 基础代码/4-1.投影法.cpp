#include <cv.h>  
#include <highgui.h>  
#include <opencv2\imgproc\imgproc.hpp>  
int main_4_1()
{
	IplImage * src = cvLoadImage("C:\\Users\\lejia\\Desktop\\pic\\投影法.jpg", 0);
	//  cvSmooth(src,src,CV_BLUR,3,3,0,0);  
	cvThreshold(src, src, 50, 255, CV_THRESH_BINARY_INV);
	IplImage* paintx = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	IplImage* painty = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	cvZero(paintx);
	cvZero(painty);
	int* v = new int[src->width];
	int* h = new int[src->height];
	memset(v, 0, src->width * sizeof(int));
	memset(h, 0, src->height * sizeof(int));
	int x, y;
	CvScalar s, t;
	//统计竖直方向投影到水平轴上目标像素数量
	for (x = 0; x<src->width; x++)
		for (y = 0; y<src->height; y++)
		{
			s = cvGet2D(src, y, x);
			if (s.val[0] == 0)
				v[x]++;
		}
	//根据统计数组打点
	for (x = 0; x<src->width; x++)
		for (y = 0; y<v[x]; y++)
		{
			t.val[0] = 255;
			cvSet2D(paintx, y, x, t);
		}
	//统计水平方向投影到竖直轴上目标像素数量
	for (y = 0; y<src->height; y++)
		for (x = 0; x<src->width; x++)
		{
			s = cvGet2D(src, y, x);
			if (s.val[0] == 0)
				h[y]++;
		}
	//根据统计数组打点
	for (y = 0; y<src->height; y++)
		for (x = 0; x<h[y]; x++)
		{
			t.val[0] = 255;
			cvSet2D(painty, y, x, t);
		}
	
	cvShowImage("二值图像", src);
	cvShowImage("垂直积分投影", paintx);
	cvShowImage("水平积分投影", painty);
	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&src);
	cvReleaseImage(&paintx);
	cvReleaseImage(&painty);
	return 0;
}