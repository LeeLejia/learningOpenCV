#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include<time.h>
#include <stdio.h>

using namespace std;
using namespace cv;

String cascadeName = "C:\\Users\\lejia\\Desktop\\opencv学习\\code\\haarcascade\\haarcascade_frontalface_alt2.xml";
String nestedCascadeName = "C:\\Users\\lejia\\Desktop\\opencv学习\\code\\haarcascade\\haarcascade_eye_tree_eyeglasses.xml";
String cascadeName2 = "C:\\Users\\lejia\\Desktop\\opencv学习\\code\\haarcascade\\aGest.xml";

CascadeClassifier cascade, nestedCascade;

void detectAndDraw(Mat& img, double scale);
void detectAndDrawInner(int scale, vector<Rect>::const_iterator &r, Mat &img, Mat &smallImg);
int main_7_1() {

	Mat frameCopy, image;
	Mat frame;
	double scale = 1;

	VideoCapture capture;
	if (!capture.open(0)) {
		cout << "打开摄像头失败！" << endl;
		return -1;
	}
	//选择并加载数据源
	if (true) {
		cascade.load(cascadeName);
		nestedCascade.load(nestedCascadeName);
	}
	else {
		cascade.load(cascadeName2);
		nestedCascade.load(cascadeName2);
	}
	while (true) {
		capture >> frame;
		detectAndDraw(frame, scale);
		if (waitKey(10) == 'q')
			break;
	}
	capture.release();
	cvDestroyWindow("result");
	return 0;
}
//找脸
void detectAndDraw(Mat& img, double scale) {
	vector<Rect> faces;
	Mat gray, smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);
	cvtColor(img, gray, CV_BGR2GRAY);
	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
	//直方图归一化
	//imshow("归一化前",smallImg);
	//equalizeHist(smallImg, smallImg);
	//imshow("归一化后", smallImg);
	//waitKey(0);

	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		| CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		| CV_HAAR_SCALE_IMAGE,
		Size(30, 30)
	);
	for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++) {
		detectAndDrawInner(scale, r, img, smallImg);
	}
	cv::imshow("result", img);
}
//找五官
void detectAndDrawInner(int scale, vector<Rect>::const_iterator &r, Mat &img, Mat &smallImg) {
	Mat smallImgROI;
	vector<Rect> nestedObjects;
	Point center;
	srand((unsigned int)time(NULL));
	Scalar color(rand() & 255, rand() & 255, rand() & 255);
	int radius;
	center.x = cvRound((r->x + r->width*0.5)*scale);
	center.y = cvRound((r->y + r->height*0.5)*scale);
	radius = cvRound((r->width + r->height)*0.25*scale);
	rectangle(img, Point(center.x + radius, center.y + radius), Point(center.x - radius, center.y - radius), color, 1, 8, 0);
	if (nestedCascade.empty())
		return;
	smallImgROI = smallImg(*r);
	nestedCascade.detectMultiScale(smallImgROI, nestedObjects,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		//|CV_HAAR_DO_CANNY_PRUNING
		| CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30));
	for (vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++) {
		center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
		center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
		radius = cvRound((nr->width + nr->height)*0.25*scale);
		circle(img, center, radius, color, 2, 8, 0);
	}
}

/*
1、bool load( const String& filename );		//加载训练好的xml文件

2、void detectMultiScale(
InputArray image,						//待检测图片
CV_OUT std::vector<Rect>& objects,	//待检测物体所在矩形区域集合（可多个）
double scaleFactor = 1.1,				//表示在前后两次相继的扫描中，搜索窗口的比例系数。
默认为1.1即每次搜索窗口依次扩大10%;
int minNeighbors = 3,					//表示构成检测目标的相邻矩形的最小个数(默认为3个)
如果组成检测目标的小矩形的个数和小于 min_neighbors - 1 都会被排除
如果min_neighbors 为 0, 则函数不做任何操作就返回所有的被检候选矩形框
int flags = 0,						//使用默认值，或者CV_HAAR_DO_CANNY_PRUNING，如果设置为后者
那么函数将会使用Canny边缘检测来排除边缘过多或过少的区域，这些区域可能不是目标所在区域
Size minSize = Size(),				//找到的目标最小尺寸，不满足则过滤
Size maxSize = Size()
);				//找到的目标最大尺寸，不满足则过滤
*/
