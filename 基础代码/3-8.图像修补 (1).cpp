#include<opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat img, inpaintMask;
Point prevPt(-1, -1);

static void onMouse(int event, int x, int y, int flags, void*)
{
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
		prevPt = Point(-1, -1);
	else if (event == EVENT_LBUTTONDOWN)
		prevPt = Point(x, y);
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (prevPt.x < 0)
			prevPt = pt;
		line(inpaintMask, prevPt, pt, Scalar::all(255), 5, 8, 0);
		line(img, prevPt, pt, Scalar::all(255), 5, 8, 0);
		prevPt = pt;
		imshow("Ô­Í¼", img);
	}
}

int main_3_8() {
	Mat img0 = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	img = img0.clone();
	inpaintMask = Mat::zeros(img.size(), CV_8U);
	imshow("Ô­Í¼", img);
	setMouseCallback("Ô­Í¼", onMouse, 0);

	while(true){
		char c = (char)waitKey();
		if (c == 27)
			break;
		else if (c == 'r'){
			inpaintMask = Scalar::all(0);
			img0.copyTo(img);
			imshow("Ô­Í¼", img);
		}else if (c == 'i' || c == ' '){
			Mat inpainted;
			//ÐèÒª²ÎÊý:Ô­Í¼,ÐÞ²¹ÇøÓò×öÎªÑÚÂë¾ØÕó,½á¹ûÍ¼,ÐÞ²¹°ë¾¶,ÐÞ²¹Ëã·¨.
			//ÐÞ²¹Ëã·¨,¿ÉÑ¡:INPAINT_NS,INPAINT_TELEA 
			inpaint(img, inpaintMask, inpainted, 3, INPAINT_NS);
			imshow("ÐÞ¸´ºó", inpainted);
			imshow("Í¼ÏñÑÚÂë", inpaintMask);
		}
	}
	return 0;
}