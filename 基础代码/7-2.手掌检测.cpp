#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main_7_2()
{
	VideoCapture cap;
	if (!cap.open(0))
		return -1;
	char ch;

	Mat img;

	vector<Rect> palm;
	vector<Rect> hands;

	CascadeClassifier Hand, Palm;

	Palm.load("C:\\Users\\lejia\\Desktop\\opencvѧϰ\\code\\haarcascade\\palm.xml");
	Hand.load("C:\\Users\\lejia\\Desktop\\opencvѧϰ\\code\\haarcascade\\hand.xml");
	while (true)
	{
		cap >> img;
		Palm.detectMultiScale(img, palm, 1.1, 3, 0 | CV_HAAR_FIND_BIGGEST_OBJECT);
		Hand.detectMultiScale(img, hands, 1.1, 3, 0 | CV_HAAR_FIND_BIGGEST_OBJECT);
		for (int i = 0, j = 0; i< hands.size() || j < palm.size(); j++, i++)
		{
			if (i< hands.size())
				circle(img, Point(hands[i].x + hands[i].width / 2, hands[i].y + hands[i].height / 2), hands[i].width / 2, Scalar(0, 255, 0), 2, 8);
			if (j < palm.size())
				circle(img, Point(palm[j].x + palm[j].width / 2, palm[j].y + palm[j].height / 2), palm[j].width / 2, Scalar(255, 0, 0), 2, 8);
		}
		imshow("Recognition", img);
		ch = waitKey(50);
		if (ch == 27)
		{
			break;
		}
	}
	return 0;
}
