// TestReadAndSaveImage.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include "HalconCpp\HalconCpp.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tchar.h>

// Use to convert bytes to KB
#define DIV 1024

// Specify the width of the field in which to print the numbers. 
// The asterisk in the format specifier "%*I64d" takes an integer 
// argument and uses it to pad and right justify the number.
#define WIDTH 7

typedef struct {
	unsigned char *Src;
	int Width;
	int Height;
} ImageParam;

bool SaveImageUsingMat(ImageParam imgParam)
{
	clock_t beginTime, endTime;
	MEMORYSTATUSEX statex, statex2;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	// method 1: Using Mat
	try
	{
		beginTime = clock();
		//cv::Mat tempImg = (cv::Mat(imgParam.Height, imgParam.Width, CV_8UC1, imgParam.Src).clone())(cv::Rect(0, 0, imgParam.Height, imgParam.Width));
		cv::Mat Img_mat = cv::Mat(imgParam.Height, imgParam.Width, CV_8UC1, imgParam.Src).clone();
		cv::imwrite("UsingMat.bmp", Img_mat.reshape(0, imgParam.Height));
		Img_mat.release();
		endTime = clock();
		std::cout << "Speed of using cv::Mat to save image = " << endTime - beginTime << " ms" << std::endl;
		_tprintf(TEXT("In SaveImageUsingMat, there is  %*ld percent of memory in use.\n"),
			WIDTH, statex.dwMemoryLoad);
		_tprintf(TEXT("In SaveImageUsingMat, there are %*I64d total KB of physical memory.\n\n"),
			WIDTH, statex.ullTotalPhys / DIV);

		return true;
	}
	catch (cv::Exception err)
	{
		std::cout << "When save image using mat have problem: " << err.what() << std::endl;

		return false;
	}
}

bool SaveImageUsingIplimage(ImageParam imgParam)
{
	clock_t beginTime, endTime;
	MEMORYSTATUSEX statex, statex2;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	// method 2: Using IplImage
	try
	{
		beginTime = clock();
		IplImage *Img_iplimage;
		Img_iplimage = ::cvCreateImageHeader(cvSize(imgParam.Width, imgParam.Height), IPL_DEPTH_8U, 1);
		::cvSetData(Img_iplimage, imgParam.Src, imgParam.Width);
		cvSaveImage("UsingIplimage.bmp", Img_iplimage);
		cvReleaseImage(&Img_iplimage);
		endTime = clock();
		std::cout << "Speed of using IplImage to save image = " << endTime - beginTime << " ms" << std::endl;
		_tprintf(TEXT("In SaveImageUsingIplimage, there is  %*ld percent of memory in use.\n"),
			WIDTH, statex.dwMemoryLoad);
		_tprintf(TEXT("In SaveImageUsingIplimage, there are %*I64d total KB of physical memory.\n\n"),
			WIDTH, statex.ullTotalPhys / DIV);

		return true;
	}
	catch (cv::Exception err)
	{
		std::cout << "When save image using iplimage have problem: " << err.what() << std::endl;

		return false;
	}
}

bool SaveImageUsingHalcon(ImageParam imgParam)
{
	clock_t beginTime, endTime;
	MEMORYSTATUSEX statex, statex2;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	// method 3: Using Halcon HImage
	try
	{
		beginTime = clock();
		/*HalconCpp::HImage Img_halcon;*/
		HalconCpp::HObject Img_halcon;
		HalconCpp::GenImage1Extern(&Img_halcon, "byte", imgParam.Width, imgParam.Height, (__int64)(imgParam.Src), 0);
		HalconCpp::WriteImage(Img_halcon, "bmp", 0, "UsingHalcon.bmp");
		endTime = clock();
		std::cout << "Speed of using Halcon, WriteImage to save image = " << endTime - beginTime << " ms" << std::endl;
		_tprintf(TEXT("In SaveImageUsingHalcon, there is  %*ld percent of memory in use.\n"),
			WIDTH, statex.dwMemoryLoad);
		_tprintf(TEXT("In SaveImageUsingHalcon, there are %*I64d total KB of physical memory.\n\n"),
			WIDTH, statex.ullTotalPhys / DIV);

		return true;
	}
	catch (HalconCpp::HException err)
	{
		std::cout << "When save image using himage have problem: " << err.ErrorMessage() << std::endl;

		return false;
	}
}

int main()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);

	cv::Mat SrcImg;
	//SrcImg = cv::imread("D:\\Document\\program\\00.TestAndLearning\\Test\\TestSaveImageSpeedBetwnOpencvAndHalcon\\x64\\Debug\\left.bmp", 0);
	SrcImg = cv::imread("G:/HIROSE_Backup/projects/00.TestAndLearning/Test/OpenCV_Test/TestSaveImageSpeedBetwnOpencv310AndHalcon/TestReadAndSaveImage/left.bmp", 0);
	
	_tprintf(TEXT("There is  %*ld percent of memory in use.\n"),
		WIDTH, statex.dwMemoryLoad);
	_tprintf(TEXT("There are %*I64d total KB of physical memory.\n\n"),
		WIDTH, statex.ullTotalPhys / DIV);
	// 2018.03.19 Due to that image is too large, opencv can't display.
	/*cv::namedWindow("test", CV_WINDOW_NORMAL);
	cv::imshow("test", SrcImg);
	cv::waitKey(0);*/

	// To simulate actual situation
	ImageParam imgParam;
	imgParam.Src = SrcImg.data;
	imgParam.Height = SrcImg.rows;
	imgParam.Width = SrcImg.cols;

	SaveImageUsingMat(imgParam);
	SaveImageUsingIplimage(imgParam);
	SaveImageUsingHalcon(imgParam);

	system("pause");
    return 0;
}

