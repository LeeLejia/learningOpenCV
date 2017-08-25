#include<opencv2\opencv.hpp>
int main()
{
	IplImage *mode = cvLoadImage("C:\\Users\\lejia\\Desktop\\pic\\1-tmp.png",0);
	IplImage *test = cvLoadImage("C:\\Users\\lejia\\Desktop\\pic\\1.png",0);
	
	CvMemStorage *mode_mems = cvCreateMemStorage();
	CvSeq *mode_seqs;
	CvMemStorage *test_mems = cvCreateMemStorage();
	CvSeq *test_seqs;

	cvFindContours(mode, mode_mems,
		&mode_seqs, sizeof(CvContour), CV_RETR_TREE);

	cvFindContours(test, test_mems,
		&test_seqs, sizeof(CvContour), CV_RETR_TREE);

	double matching = cvMatchShapes(test, mode, 3);
	printf("图像的比较结果：%f\n", matching);
	matching = cvMatchShapes(test_seqs, mode_seqs, 3);
	printf("轮廓的比较结果：%f\n", matching);

	cvReleaseImage(&mode);
	cvReleaseImage(&test);
	system("pause");
	return 1;
}


/*
	MatchShapes 比较两个形状
	函数原型：
	double cvMatchShapes( 
						const void* object1,  //第一个轮廓或灰度图像
						const void* object2,  //第二个轮廓或灰度图像
						int method,			  //比较方法：	 
												CV_CONTOUR_MATCH_I1, CV_CONTOURS_MATCH_I2 or CV_CONTOURS_MATCH_I3.等
												三个实现方法全部使用 Hu 矩 (见 cvGetHuMoments)
						double parameter=0	  //比较方法的参数 (目前不用)，仅做保留
						);
	对比的两张图片互换位置后结果不一样，同一张图片对比结果为0。
*/