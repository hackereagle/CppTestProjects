#include <opencv2/opencv.hpp>
#include <iostream>
//#include <D:/Program Files/opencv/opencv_contrib-3.1.0/install/include/opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/features2d.hpp>
#include <vector>
#include <ctime>

void makeTestingImage_NoHaveTemplate(cv::Mat& src, cv::Mat& templ, float angle = 0.0)
{
	cv::Mat input = cv::imread("D:/Document/project/PMISH_Tech/05.TemplateMatchingFindMark/Image/relative wafer images/default.png", 0);
	//EnhenceEdge(input, input);
	//ExtractEdge(input, input);

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

	cv::Mat otherImg = cv::imread("D:/Document/project/PMISH_Tech/05.TemplateMatchingFindMark/Image/relative wafer images/real1.png", 0);
	src = input_r(src_ROI).clone();
	templ = otherImg(templ_ROI).clone();
}

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
	EnhenceEdge(input, input);
	ExtractEdge(input, input);

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

void main()
{
	cv::Mat src, templ;
	makeTestingImage(src, templ, 30.0);
	//makeTestingImage_NoHaveTemplate(src, templ, 30.0); // test input image don't have mark. If input image don't have mark, result would be very strange. 

	clock_t begin = clock();
	// extract feature by ORB
	cv::Ptr<cv::Feature2D> orb = cv::ORB::create();
	std::vector<cv::KeyPoint> keypoint1, keypoint2;
	cv::Mat descriptors1, descriptors2;
	orb->detectAndCompute(templ, cv::Mat(), keypoint1, descriptors1);
	orb->detectAndCompute(src, cv::Mat(), keypoint2, descriptors2);

	// match feature
	std::vector<cv::DMatch> matches;
	cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");
	matcher->match(descriptors1, descriptors2, matches, cv::Mat());

	// choose great matching
	std::sort(matches.begin(), matches.end());
	int numGoodMatches = matches.size() * 0.15;
	matches.erase(matches.begin() + numGoodMatches, matches.end());

	// debug! draw matching result
	cv::Mat drawMat;
	cv::drawMatches(templ, keypoint1, src, keypoint2, matches, drawMat);

	// take great matching points
	std::vector<cv::Point2f> points1, points2;
	for (size_t i = 0; i < matches.size(); i++) {
		int idx1 = matches[i].queryIdx;
		points1.push_back(keypoint1[idx1].pt);

		int idx2 = matches[i].trainIdx;
		points2.push_back(keypoint2[idx2].pt);
	}

	// calculate homogenous matrix
	cv::Mat Matrix = cv::findHomography(points2, points1, cv::RANSAC);
	clock_t end = clock();
	cv::Mat result;
	cv::warpPerspective(src, result, Matrix, templ.size());

	std::cout << "total elscape time = " << end - begin << " ms" << std::endl;
	
	//cv::namedWindow("mapping points", cv::WINDOW_NORMAL);
	//cv::imshow("mapping points", drawMat);
	//cv::waitKey(0);

	//cv::namedWindow("result", cv::WINDOW_NORMAL);
	//cv::imshow("result", result);
	//cv::waitKey(0);

	system("pause");
}
