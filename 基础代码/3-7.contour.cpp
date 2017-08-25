#include <stdio.h>
#include <cv.h>
#include <cxcore.h>   
#include <highgui.h>  

// 内轮廓填充   
// 参数:   
// 1. pBinary: 输入二值图像，单通道，位深IPL_DEPTH_8U。  
// 2. dAreaThre: 面积阈值，当内轮廓面积小于等于dAreaThre时，进行填充。   
void FillInternalContours(IplImage *pBinary)
{
	double dConArea;
	CvSeq *pContour = NULL;
	CvSeq *pConInner = NULL;
	CvMemStorage *pStorage = NULL;
	// 执行条件   
	if (!pBinary)
		return;
	// 查找所有轮廓   
	pStorage = cvCreateMemStorage(0);
	cvFindContours(pBinary, pStorage, &pContour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	// 填充所有轮廓   
	cvDrawContours(pBinary, pContour, CV_RGB(255, 255, 255), CV_RGB(255, 255, 255), 2, CV_FILLED, 8, cvPoint(0, 0));
	// 外轮廓循环   
	int wai = 0;
	int nei = 0;
	for (; pContour != NULL; pContour = pContour->h_next)
	{
		wai++;
		// 内轮廓循环   
		for (pConInner = pContour->v_next; pConInner != NULL; pConInner = pConInner->h_next)
		{
			nei++;
			// 内轮廓面积   
			dConArea = fabs(cvContourArea(pConInner, CV_WHOLE_SEQ));
			printf("%f\n", dConArea);
		}
		CvRect rect = cvBoundingRect(pContour, 0);
		cvRectangle(pBinary, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), CV_RGB(255, 255, 255), 1, 8, 0);
	}

	printf("wai = %d, nei = %d", wai, nei);
	cvReleaseMemStorage(&pStorage);
	pStorage = NULL;
}
int Otsu(IplImage* src)
{
	int height = src->height;
	int width = src->width;

	//histogram      
	float histogram[256] = { 0 };
	for (int i = 0; i < height; i++)
	{
		unsigned char* p = (unsigned char*)src->imageData + src->widthStep * i;
		for (int j = 0; j < width; j++)
		{
			histogram[*p++]++;
		}
	}
	//normalize histogram      
	int size = height * width;
	for (int i = 0; i < 256; i++)
	{
		histogram[i] = histogram[i] / size;
	}

	//average pixel value      
	float avgValue = 0;
	for (int i = 0; i < 256; i++)
	{
		avgValue += i * histogram[i];  //整幅图像的平均灰度    
	}

	int threshold;
	float maxVariance = 0;
	float w = 0, u = 0;
	for (int i = 0; i < 256; i++)
	{
		w += histogram[i];  //假设当前灰度i为阈值, 0~i 灰度的像素(假设像素值在此范围的像素叫做前景像素) 所占整幅图像的比例    
		u += i * histogram[i];  // 灰度i 之前的像素(0~i)的平均灰度值： 前景像素的平均灰度值    
		float t = avgValue * w - u;
		float variance = t * t / (w * (1 - w));
		if (variance > maxVariance)
		{
			maxVariance = variance;
			threshold = i;
		}
	}

	return threshold;
}

int main_3_7()
{
	IplImage *img = cvLoadImage("C:\\Users\\lejia\\Desktop\\pic\\1.png", 0);
	IplImage *bin = cvCreateImage(cvGetSize(img), 8, 1);

	int thresh = Otsu(img);
	cvThreshold(img, bin, thresh, 255, CV_THRESH_BINARY);

	FillInternalContours(bin);

	cvNamedWindow("img");
	cvShowImage("img", img);

	cvNamedWindow("result");
	cvShowImage("result", bin);

	cvWaitKey(-1);

	cvReleaseImage(&img);
	cvReleaseImage(&bin);

	return 0;
}