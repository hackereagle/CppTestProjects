#include "opencv2\opencv.hpp"
#include <time.h>
#include <iostream>

using namespace cv;

void CalculateUsingImagedataArray(Mat Img)
{
	int i, j;
	unsigned long int sum;

	sum = 0;
	for (i = 0; i < (Img.cols * Img.rows); i++)
		sum += Img.data[i];

	std::cout << "array sum: " << sum << std::endl;
}

void CalculateUsingImagedataPointer(Mat Img)
{
	int i, j;
	unsigned long int sum;

	sum = 0;
	for (i = 0; i < (Img.cols * Img.rows); i++)
		sum += *(Img.data + i);

	std::cout << "array sum: " << sum << std::endl;
}

void CalculateUsingMatiterator(Mat Img)
{
	int sum;
	MatIterator_<uchar> begin = Img.begin<uchar>();
	MatIterator_<uchar> end = Img.end<uchar>();

	sum = 0;
	for (begin; begin != end; begin++)
		sum += *begin;

	std::cout << "iterator sum: " << sum << std::endl;
}

void CalculateUsingPtr(Mat Img)
{
	int i, sum;

	sum = 0;
	for (i = 0; i < (Img.cols * Img.rows); i++)
		sum += *(Img.ptr<uchar>(0) + i);

	std::cout << "ptr sum: " << sum << std::endl;
}

void main()
{
	Mat Img;
	Img = imread("D:\\Document\\program\\03.SealÀË´ú\\SEAL¼Ë«~¹Ï\\T1_20170607\\1\\1.bmp", CV_LOAD_IMAGE_GRAYSCALE);

	int t1_0, t1_1, t2_0, t2_1, t3_0, t3_1;
	t1_0 = clock();
	CalculateUsingImagedataArray(Img);
	t1_1 = clock();

	t2_0 = clock();
	CalculateUsingImagedataPointer(Img);
	t2_1 = clock();

	std::cout << "Using array take " << t1_1 - t1_0 << "ms !" << std::endl;
	std::cout << "Using pointer take " << t2_1 - t2_0 << "ms !" << std::endl;

	system("pause");
}