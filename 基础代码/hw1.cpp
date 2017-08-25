#include <opencv2\opencv.hpp>  
#include <opencv2\imgproc\imgproc.hpp>  
#include<iostream>
using namespace std;
using namespace cv;

//随机获取0-9，且每个数字只被获取一次
int getSrcFlag() {
	//标记图片的9个小方块
	static bool flag[9] = { 0 };
	srand((unsigned)time(NULL));
	int f;
	do{
		f = rand() % 9;
	} while (flag[f]);
	flag[f] = true;
	return f;
}
//fromIndex:原图子图编号（0-8），toIndex:目标图子图编号（0-8）
void getChildMat(Mat &src,Mat &dst,int fromIndex,int toIndex,int size) {
	if (fromIndex < 0 || fromIndex>8 ||toIndex<0 || toIndex>8)
		return;
	//分别计算主图和目标图的子图所在范围，利用Range创建一个内存共享的子图的原理
	//对目标图的子图进行覆盖，在覆盖子图的同时，目标原图被修改。
	Mat from = src(Range(size*(fromIndex % 3), size*(fromIndex % 3)+size), Range(size*(fromIndex / 3), size*(fromIndex / 3) + size));
	Mat to=dst(Range(size*(toIndex / 3), size*(toIndex / 3) + size), Range(size*(toIndex % 3), size*(toIndex % 3) + size));
	from.copyTo(to);
}
int main()
{
	//读入图像  
	Mat src = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	//设置小方块尺寸。
	int size=(src.cols > src.rows ? src.rows : src.cols) / 3;
	resize(src,src, Size(size*3,size*3), 0, 0, INTER_LINEAR);
	Mat dst(src.size(), src.type());
	imshow("原图", src);
	for (int i = 0; i < 9; i++)
		getChildMat(src,dst,getSrcFlag(),i,size);
	imshow("九宫图", dst);
	imwrite("C:\\Users\\lejia\\Desktop\\pic\\9path.png",dst);
	waitKey();
	return 0;
}