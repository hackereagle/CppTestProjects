#include <opencv2\opencv.hpp>

void main()
{
	cv::Mat A = cv::Mat(3, 3, CV_32FC1);
	A = (cv::Mat_<float>(3, 3) << 1, 2, 3,
								  4, 5, 6,
								  7, 8, 9);
	cv::Mat B = cv::Mat(3, 3, CV_32FC1);
	B = (cv::Mat_<float>(3, 3) << 2, 0, 0,
								  0, 2, 0,
								  0, 0, 2);
	cv::Mat C = A * B;
	std::cout << "A * B = " << C << std::endl;

	double D = A.dot(B);
	std::cout << "\nA . B = " << D << std::endl;

	cv::Mat E = A.mul(B, 3);
	std::cout << "\nA .* B .* 3 = " << E << std::endl;

	double temp[9]{ 0.1, 0.2, 0.3,
		0.4, 0.5, 0.6,
		0.7, 0.8,  0.9 };
	cv::Mat* test = new cv::Mat(3, 3, CV_64FC1, (void*)temp);
	std::cout << "\n" << *test << std::endl;

	*test = 1 + *test;
	std::cout << "\n1 + test = \n" << *test << std::endl;

	*test = 20 * *test;
	std::cout << "\n20 * test = \n" << *test << std::endl;


	// test solve 
	cv::Mat F, G, H;


	system("pause");
}