#include<stdio.h>  
#include<cv.h>  
#include<highgui.h>  
int main()
{
	IplImage* image = cvLoadImage("C:\\Users\\lejia\\Desktop\\pic\\lines.png", 0); //加载图像  
	IplImage* dst = cvCreateImage(cvGetSize(image), 8, 3);
	cvCanny(image, image, 100, 255);//查找边缘  
	cvCvtColor(image, dst, CV_GRAY2BGR);//转换到彩色空间  
	CvMemStorage* storage = cvCreateMemStorage(0); //创建直线的存储空间  
	CvSeq* seq = NULL;
	seq = cvHoughLines2(image, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI / 180, 50, 10, 15);//哈夫变换检测直线  

	for (int i = 0; i<seq->total; i++)
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(seq, i);
		cvLine(dst, line[0], line[1], CV_RGB(255, 0, 0), 1, 8, 0);
	}

	cvNamedWindow("边缘图片", 1);
	cvNamedWindow("检测结果", 1);
	cvShowImage("边缘图片", image);
	cvShowImage("检测结果", dst);
	cvWaitKey(0);

	//释放内存空间  
	cvReleaseImage(&image);
	cvReleaseImage(&dst);
	cvDestroyWindow("cc");
	cvDestroyWindow("边缘图片");
	cvDestroyWindow("检测结果");
	cvReleaseMemStorage(&storage);
	return 0;
}