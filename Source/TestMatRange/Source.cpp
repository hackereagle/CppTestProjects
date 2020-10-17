#include <iostream>
#include <opencv2/opencv.hpp>

int main(void)
{
	double *temp = new double[10]{ 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
	cv::Mat TestMat = cv::Mat(5, 2, CV_64FC1, temp);
	std::cout << "matrix = \n" << TestMat << std::endl;

	cv::Mat firstCol = TestMat.colRange(0, 1);
	std::cout << "\nfirst column of matrix = \n" << firstCol << std::endl;
	cv::Mat secondCol = TestMat.colRange(1, 2);
	std::cout << "\nsecond column of matrix = \n" << secondCol << std::endl;

	system("pause");
	return 1;
}