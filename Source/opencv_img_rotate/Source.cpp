#include <iostream>
#include "opencv2/opencv.hpp"

#define DEGREE_TO_RAD(x) (((x) / 180.0) * CV_PI)
#define RAD_TO_DEGREE(x) (((x) / CV_PI) * 180.0)

cv::Mat getGaussKernel(double sigmax, double sigmay, int ksize, double theta)
{
	int mid = ksize >> 1;
	std::cout << "in getGaussKernel: mid = " << mid << std::endl;
	const double x_spreed = 1.0 / (sigmax * sigmax * 2);
	const double y_spreed = 1.0 / (sigmay * sigmay * 2);
	const double denominator = 2 * CV_PI * sigmax * sigmay; //8 * std::atan(1) * sigmax * sigmay;

	std::vector<double> gauss_x, gauss_y;
	gauss_x.reserve(ksize);
	for (int i = 0; i < ksize; i++) {
		int x = i - mid;
		gauss_x.push_back(std::exp(-x * x * x_spreed));
	}

	gauss_y.reserve(ksize);
	for (int i = 0; i < ksize; i++) {
		int y = i - mid;
		gauss_y.push_back(std::exp(-y * y * y_spreed));
	}

	cv::Mat kernel = cv::Mat::zeros(ksize, ksize, CV_32FC1);
	for (int j = 0; j < ksize; j++)
		for (int i = 0; i < ksize; i++)
			*(reinterpret_cast<float*>(kernel.data) + (j * ksize) + i) = gauss_x[i] * gauss_y[j] / denominator;

	//cv::Mat r = cv::getRotationMatrix2D(cv::Point(mid, mid), RAD_TO_DEGREE(theta), 1.0);
	cv::Mat r = cv::getRotationMatrix2D(cv::Point(mid, mid), theta, 1.0);
	cv::warpAffine(kernel, kernel, r, kernel.size(), cv::INTER_CUBIC);
	return kernel;
}

int main()
{
	cv::Mat vsem_img = getGaussKernel(2, 6, 21, 20);

	double theta = 30;
	cv::Mat srcImg = cv::imread("D:\\Document\\project\\PMISH_Tech\\06.SEM_Auto_Focus_Algorithm\\Testing\\Test_matlab_opencv_img_rotate\\OneLine_gray.bmp", CV_LOAD_IMAGE_GRAYSCALE);

	cv::Mat rotatedImg_center;
	cv::Mat r1 = cv::getRotationMatrix2D(cv::Point(srcImg.cols / 2, srcImg.rows / 2), theta, 1.0);
	cv::warpAffine(srcImg, rotatedImg_center, r1, srcImg.size(), cv::INTER_CUBIC);

	cv::Mat rotatedImg_org;
	cv::Mat r2 = cv::getRotationMatrix2D(cv::Point(0, 0), theta, 1.0);
	cv::warpAffine(srcImg, rotatedImg_org, r2, srcImg.size(), cv::INTER_CUBIC);
	

	system("pause");
	return 0;
}
