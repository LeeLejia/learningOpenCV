#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main_6_1(){
	Mat src = imread("C:\\Users\\lejia\\Desktop\\pic\\lines.png",0);
	imshow("灰度图", src);
	//先做二值化处理
	threshold(src, src, 100, 255, THRESH_BINARY);
	//用以存放轮廓的集合
	vector<vector<Point>> contours;
	findContours(src, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	Mat crop;
	for (vector<vector<Point>>::iterator it = contours.begin(); it != contours.end(); it++) {
		//从点集中获取最大的外切矩形
		Rect rect = boundingRect(*it);
		//该处过滤小的轮廓
		if (rect.width<20 || rect.height<20)
			continue;
		crop = src(Range(rect.y, rect.y + rect.height), Range(rect.x, rect.x + rect.width));
		//计算出轮廓的面积并输出
		char str[15];
		sprintf(str,"面积%f",contourArea(*it));
		cout << str << endl;
		
		sprintf(str, "周长 closed：%f", arcLength(*it,true));
		cout << str << endl;
		sprintf(str, "周长：%f", arcLength(*it, false));
		cout << str << endl;
		imshow("轮廓", crop);
		cvWaitKey(0);
	}
	//画出全部轮廓
	Mat contoursImage(src.rows, src.cols, CV_8UC3, Scalar(255,255,255));
	for (int i = 0, srand((unsigned)time(NULL)); i < contours.size(); i++) {
		//该函数中i如果为-1则画出全部的轮廓，此时不需要外层for循环
		drawContours(contoursImage, contours, i, Scalar(rand() & 255, rand() & 255, rand() & 255), 2);
	}
	imshow("轮廓", contoursImage);
	waitKey(0);
	src.release();
	cvDestroyAllWindows();
	return 0;
}
/*
	1、findContours 函数原型为：
	void findContours(
					  InputOutputArray image,			//输入一个2值化过的单通道图像（边缘提取或阈值化）
					  OutputArrayOfArrays contours,		//检测到的轮廓集合，每个轮廓又是个点集：
														  vector<vector<Point>> contours
					  OutputArray hierarchy,			//返回层级集合，和返回轮廓数量相同。
														  每个轮廓contours[ i ]对应4个元素：
														  hierarchy[ i ][ 0 ] ~hierarchy[ i ][ 3 ]
														  分别表示后一个轮廓、前一个轮廓、父轮廓、内嵌轮廓的索引编号，如果没有对应项，该值设置为负数。
														 
					  int mode,							 //mode表示轮廓的检索模式:
														   CV_RETR_EXTERNAL	表示只检测外轮廓
														   CV_RETR_LIST		检测的轮廓不建立等级关系
														   CV_RETR_CCOMP	建立两个等级的轮廓，上面的一层为外边界，里面的一层为内孔的边界信息。如果内孔内还有一个连通物体，这个物体的边界也在顶层。
														   CV_RETR_TREE		建立一个等级树结构的轮廓。具体参考contours.c这个demo
					  int method,						 //method为轮廓的近似办法:
														   CV_CHAIN_APPROX_NONE		存储所有的轮廓点，相邻的两个点的像素位置差不超过1，即max（abs（x1-x2），abs（y2-y1））==1
														   CV_CHAIN_APPROX_SIMPLE	压缩水平方向，垂直方向，对角线方向的元素，只保留该方向的终点坐标，例如一个矩形轮廓只需4个点来保存轮廓信息
														   CV_CHAIN_APPROX_TC89_L1，CV_CHAIN_APPROX_TC89_KCOS使用teh-Chinl chain 近似算法		 
					  Point offset=Point()				 //offset表示代表轮廓点的偏移量:
														   可以设置为任意值。对ROI图像中找出的轮廓，并要在整个图像中进行分析时，这个参数还是很有用的。
					  );
	tip: findContours后的轮廓信息可能过于复杂不平滑，可以用approxPolyDP函数对该多边形曲线做适当近似。
	
	2、contourArea 函数可以得到当前轮廓包含区域的大小，方便轮廓的筛选。
	
	3、drawContours 函数用于将一个轮廓画出。函数原型：
	void drawContours( InputOutputArray image,			//画到的图像						
					   InputArrayOfArrays contours,		//轮廓集合（只会画出集合中的一个轮廓元素，或全部）
                       int contourIdx,					//指明画出第几个轮廓（）
					   const Scalar& color,				//画出颜色
                       int thickness = 1,				//画出线宽（为负值或CV_FILLED则是填充轮廓内部）
					   int lineType = LINE_8,			//线的类型，如虚线，实线，无锯齿线条等
                       InputArray hierarchy = noArray(),//轮廓结构信息
                       int maxLevel = INT_MAX,			
					   Point offset = Point() 
					  );
	4、convexHull 复杂轮廓往往不适合特征的检测，使用该函数用于简化轮廓结构，获取轮廓外凸包络的点集

	5、boundingRect 得到轮廓的外包络矩形（正放的矩形）

	6、minAreaRect 得到旋转的外包络矩形，返回值为RotatedRect

	7、minEnclosingCircle 得到轮廓的外包络圆

	8、fitEllipse 得到轮廓的外包络椭圆，返回值也是RotatedRect，用ellipse函数画出对应的椭圆

	9、moments 根据多边形的轮廓信息得到多边形的多阶矩，这个类可以得到多边形和光栅形状的3阶以内的所有矩，类内有变量m00，m10，m01，m20，m11，m02，m30，m21，m12，m03，比如多边形的质心为 x = m10 / m00，y = m01 / m00。

	10、pointPolygonTest 获得某点与轮廓的距离，返回值为该点距离轮廓最近边界的距离（正值为在轮廓内部，负值为在轮廓外部，0表示在边界上）

*/