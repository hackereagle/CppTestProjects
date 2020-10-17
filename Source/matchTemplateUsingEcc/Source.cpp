#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

bool ExtractEdge(cv::Mat srcImg, cv::Mat& edge)
{
	try {
		CV_Assert(!srcImg.empty());

		int canny_threshold1 = 50;
		int canny_threshold2 = 185;
		int knerlSize = 5;// 3;
		int filterSize = 5;

		cv::Mat Temp;
		//cv::blur(srcImg, Temp, cv::Size(knerlSize, knerlSize));
		cv::GaussianBlur(srcImg, Temp, cv::Size(knerlSize, knerlSize), 5, 5);
		//cv::bilateralFilter(srcImg, Temp, 5, 30, 30);
		cv::Canny(Temp, edge, canny_threshold1, canny_threshold2, filterSize);
		Temp.release();

	}
	catch (cv::Exception ex) {
		std::cout << "In FindAlignmentMark::ExtractEdge, " << ex.what() << std::endl;
		return false;
	}
	catch (std::exception ex) {
		std::cout << "In FindAlignmentMark::ExtractEdge, " << ex.what() << std::endl;
		return false;
	}
	catch (...){
		std::cout << "In FindAlignmentMark::ExtractEdge have other problem!" << std::endl;
		return false;
	}
	return true;
}

bool EnhenceEdge(cv::Mat srcImg, cv::Mat& enhence_edge)
{
	try {
		CV_Assert(!srcImg.empty());

		cv::Mat Temp, lap;
		cv::GaussianBlur(srcImg, Temp, cv::Size(3, 3), 5, 5);
		cv::Laplacian(Temp, lap, CV_64F);
		cv::convertScaleAbs(lap, lap);
		enhence_edge = srcImg - lap;
		Temp.release(); lap.release();
	}
	catch (cv::Exception ex) {
		std::cout << "In FindAlignmentMark::EhenceEdge, " << ex.what() << std::endl;
		return false;
	}
	catch (std::exception ex) {
		std::cout << "In FindAlignmentMark::EhenceEdge, " << ex.what() << std::endl;
		return false;
	}
	catch (...) {
		std::cout << "In FindAlignmentMark::EhenceEdge have other problem!" << std::endl;
		return false;
	}
	return true;
}

// angle is degree!
void makeTestingImage(cv::Mat& src, cv::Mat& templ, float angle = 0.0)
{
	cv::Mat input = cv::imread("D:/Document/project/PMISH_Tech/05.TemplateMatchingFindMark/Image/relative wafer images/default.png", 0);
	/*EnhenceEdge(input, input);
	ExtractEdge(input, input);*/

	cv::Mat input_r;
	if (angle != 0.0) {
		cv::Mat rotateMat = getRotationMatrix2D(cv::Point2f(static_cast<float>(input.cols) / 2.0, static_cast<float>(input.rows) / 2.0),
										angle, 1);
		cv::warpAffine(input, input_r, rotateMat, input.size());
	}
	else {
		input_r = input.clone();
	}
	
	const int width = 512, height = 512;
	cv::Rect templ_ROI = cv::Rect(890, 780, width, height);
	cv::Rect src_ROI = cv::Rect(900, 800, width, height);

	src = input_r(src_ROI).clone();
	templ = input(templ_ROI).clone();
}

int main()
{
	//載入
	//Mat templ = imread("D:/Document/project/PMISH_Tech/05.TemplateMatchingFindMark/Image/relative wafer images/template/template_thin.bmp", 0);
	//Mat src = imread("D:/Document/project/PMISH_Tech/05.TemplateMatchingFindMark/Image/relative wafer images/default.png", 0);
	cv::Mat src, templ;
	makeTestingImage(src, templ, 30.0);
	
	//定義運動模型
	const int warp_mode = cv::MOTION_EUCLIDEAN; //MOTION_EUCLIDEAN; MOTION_AFFINE
	//建立變化矩陣
	Mat warp_matrix;
	if (warp_mode == MOTION_HOMOGRAPHY)
		warp_matrix = Mat::eye(3, 3, CV_32F);
	else
		warp_matrix = Mat::eye(2, 3, CV_32F);
	//最大疊代數
	int number_of_iterations = 200; // 5000;
	//疊代精度
	double termination_eps = 1e-10;
	//疊代標準
	TermCriteria criteria(TermCriteria::COUNT + TermCriteria::EPS,
		number_of_iterations, termination_eps);
	//計算變換矩陣
	findTransformECC(templ, src, warp_matrix, warp_mode, criteria);
	//findTransformECC(src, templ, warp_matrix, warp_mode, criteria);
	//計算對齊後的影象
	Mat result;
	if (warp_mode != MOTION_HOMOGRAPHY)
		//warpAffine(src, result, warp_matrix, templ.size(), INTER_LINEAR + WARP_INVERSE_MAP);
		warpAffine(src, result, warp_matrix, templ.size());
	else
		warpPerspective(src, result, warp_matrix, templ.size(), INTER_LINEAR + WARP_INVERSE_MAP);

	//if (warp_mode != MOTION_HOMOGRAPHY)
	//	warpAffine(templ, result, warp_matrix, src.size(), INTER_LINEAR + WARP_INVERSE_MAP);
	//else
	//	warpPerspective(templ, result, warp_matrix, src.size(), INTER_LINEAR + WARP_INVERSE_MAP);
	

	return 0;
}