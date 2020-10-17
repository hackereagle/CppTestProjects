#include <opencv2\opencv.hpp>
#include "DrawRoi.h"

DrawRoi::DrawRoi()
{
	_color = cv::Scalar(0, 0, 255);
}

DrawRoi::~DrawRoi()
{
}

void DrawRoi::setDrawColor(cv::Scalar color)
{
	_color = color;
}

void DrawRoi::onMouse(int Event, int x, int y, int flag, void* param)
{
	DrawRoi *_temp = static_cast<DrawRoi*>(param);
	_temp->MouseEven(Event, x, y, flag);
}

void DrawRoi::MouseEven(int Event, int x, int y, int flag)
{
	if (Event == CV_EVENT_LBUTTONDOWN)
		VertexLeftTop = cv::Point(x, y);

	if (Event == CV_EVENT_LBUTTONUP)
	{
		VertexRightdown = cv::Point(x, y);
		tempVertexRightdown = cv::Point(-1, -1);
	}

	if (Event == CV_EVENT_MOUSEMOVE && flag == cv::EVENT_FLAG_LBUTTON)
		tempVertexRightdown = cv::Point(x, y);

	if (Event == CV_EVENT_RBUTTONUP)
		tempVertexRightdown = cv::Point(-2, -2);
}

int DrawRoi::MouseStatu()
{
	if (tempVertexRightdown.x == -2 && tempVertexRightdown.y == -2)
		return enumMouseStatu::EndDraw;

	if (VertexLeftTop.x == -1 && VertexRightdown.x == -1)
		return enumMouseStatu::MouseNoActivity;
	else if (VertexLeftTop.x != -1 && tempVertexRightdown.x != -1)
		return enumMouseStatu::MouseHaul;
	else if (VertexLeftTop.x != -1 && VertexRightdown.x != -1)
		return enumMouseStatu::FinishingRoi;
}

void DrawRoi::DrawRectangle(cv::String WindowsName, cv::Mat srcImg)
{
	// check window whether exist.
	if (!cvGetWindowHandle(WindowsName.c_str()))
	{
		std::cout << "Window \"" << WindowsName << "\" isn\'t exist!" << std::endl;
		return;
	}

	cv::Mat srcImg_color;
	if (srcImg.channels() == 1)
		cv::cvtColor(srcImg, srcImg_color, cv::COLOR_GRAY2BGR);
	else if(srcImg.channels() >= 3)
		srcImg_color = srcImg.clone();
	else
	{
		std::cout << "Please check format of your input image!" << std::endl;
		return;
	}

	cv::imshow(WindowsName, srcImg_color);
	cv::setMouseCallback(WindowsName, onMouse, this);

	bool drawingRoi = true;
	while (drawingRoi)
	{
		
		if (MouseStatu() == enumMouseStatu::MouseNoActivity)
			cv::imshow(WindowsName, srcImg_color);

		if (MouseStatu() == enumMouseStatu::MouseHaul)
		{
 			cv::Mat tempImg = srcImg_color.clone();
			cv::rectangle(tempImg, cv::Rect(VertexLeftTop, tempVertexRightdown), _color, 2);
			cv::imshow(WindowsName, tempImg);
		}

		if (MouseStatu() == enumMouseStatu::FinishingRoi)
		{
			cv::rectangle(srcImg_color, cv::Rect(VertexLeftTop, VertexRightdown), _color, 2);

			RoiInformation.LeftTopPoint.x = VertexLeftTop.x;
			RoiInformation.LeftTopPoint.y = VertexLeftTop.y;
			RoiInformation.width = VertexRightdown.x - VertexLeftTop.x;
			RoiInformation.height = VertexRightdown.y - VertexLeftTop.y;

			VertexLeftTop = cv::Point(-1, -1);
			VertexRightdown = cv::Point(-1, -1);
			cv::imshow(WindowsName, srcImg_color);
		}

		if (cv::waitKey(33) == 27) // pressing "esc" is mean redrawing ROI. 
		{
			if (srcImg.channels() == 1)
				cv::cvtColor(srcImg, srcImg_color, cv::COLOR_GRAY2BGR);
			else
				srcImg_color = srcImg.clone();

			cv::imshow(WindowsName, srcImg_color);
		}

		if(MouseStatu() == enumMouseStatu::EndDraw)
			drawingRoi = false;
	}

	RoiInformation.type = enumRoiType::RECTANGLE;
	RoiInformation.center.x = RoiInformation.LeftTopPoint.x + (RoiInformation.width >> 1);
	RoiInformation.center.y = RoiInformation.LeftTopPoint.y + (RoiInformation.height >> 1);
	RoiImg = srcImg(cv::Rect(RoiInformation.LeftTopPoint.x, RoiInformation.LeftTopPoint.y, RoiInformation.width, RoiInformation.height));

	cv::destroyAllWindows();
}

void DrawRoi::DrawCircle(cv::String WindowsName, cv::Mat srcImg)
{
	// check window whether exist.
	if (!cvGetWindowHandle(WindowsName.c_str()))
	{
		std::cout << "Window \"" << WindowsName << "\" isn\'t exist!" << std::endl;
		return;
	}

	cv::Mat srcImg_color;
	if (srcImg.channels() == 1)
		cv::cvtColor(srcImg, srcImg_color, cv::COLOR_GRAY2BGR);
	else if (srcImg.channels() >= 3)
		srcImg_color = srcImg.clone();
	else
	{
		std::cout << "Please check format of your input image!" << std::endl;
		return;
	}

	cv::imshow(WindowsName, srcImg_color);
	cv::setMouseCallback(WindowsName, onMouse, this);

	bool drawingRoi = true;
	while (drawingRoi)
	{

		if (MouseStatu() == enumMouseStatu::MouseNoActivity)
			cv::imshow(WindowsName, srcImg_color);

		if (MouseStatu() == enumMouseStatu::MouseHaul)
		{
			cv::Mat tempImg = srcImg_color.clone();
			cv::Point center = cv::Point((tempVertexRightdown.x + VertexLeftTop.x) >> 1, (tempVertexRightdown.y + VertexLeftTop.y) >> 1);
			int radius = (tempVertexRightdown.x - VertexLeftTop.x) >> 1;
			radius = radius > 0 ? radius : -radius;
			cv::circle(tempImg, center, radius, cv::Scalar(0, 0, 255), 2, -1);
			cv::imshow(WindowsName, tempImg);
		}

		if (MouseStatu() == enumMouseStatu::FinishingRoi)
		{
			cv::Point center = cv::Point((VertexRightdown.x + VertexLeftTop.x) >> 1, (VertexRightdown.y + VertexLeftTop.y) >> 1);
			int radius = (VertexRightdown.x - VertexLeftTop.x) >> 1;
			radius = radius > 0 ? radius : -radius;
			cv::circle(srcImg_color, center, radius, cv::Scalar(0, 0, 255), 2, -1);

			RoiInformation.width = VertexRightdown.x - VertexLeftTop.x;
			RoiInformation.height = RoiInformation.width;
			RoiInformation.LeftTopPoint.x = center.x - (RoiInformation.width >> 1);
			RoiInformation.LeftTopPoint.y = center.y - (RoiInformation.height >> 1);

			VertexLeftTop = cv::Point(-1, -1);
			VertexRightdown = cv::Point(-1, -1);
			cv::imshow(WindowsName, srcImg_color);
		}

		if (cv::waitKey(33) == 27) // pressing "esc" is mean redrawing ROI. 
		{
			if (srcImg.channels() == 1)
				cv::cvtColor(srcImg, srcImg_color, cv::COLOR_GRAY2BGR);
			else
				srcImg_color = srcImg.clone();

			cv::imshow(WindowsName, srcImg_color);
		}

		if (MouseStatu() == enumMouseStatu::EndDraw)
			drawingRoi = false;
	}

	RoiInformation.type = enumRoiType::CIRCLE;
	RoiInformation.center.x = RoiInformation.LeftTopPoint.x + (RoiInformation.width >> 1);
	RoiInformation.center.y = RoiInformation.LeftTopPoint.y + (RoiInformation.height >> 1);
	cv::Mat CircleMask(cv::Size(RoiInformation.height, RoiInformation.width), srcImg.type(), cv::Scalar::all(0));
	cv::Mat tempRoiImg = srcImg(cv::Rect(RoiInformation.LeftTopPoint.x, RoiInformation.LeftTopPoint.y, RoiInformation.width, RoiInformation.height));
	cv::circle(CircleMask, cv::Point(RoiInformation.width >> 1, RoiInformation.width >> 1), RoiInformation.width >> 1, cv::Scalar::all(255), -1);
	RoiImg = CircleMask & tempRoiImg;

	cv::destroyAllWindows();
}

void DrawRoi::showRoiImage()
{
	if (RoiImg.empty())
	{
		std::cout << "ROI image is empty! \nPlease read a image and draw ROI!" << std::endl;
		return;
	}

	cv::namedWindow("ROI Image", CV_WINDOW_NORMAL);
	cv::resizeWindow("ROI Image", RoiInformation.width, RoiInformation.height);
	cv::imshow("ROI Image", RoiImg);
	cv::waitKey(0);
}

bool DrawRoi::SaveRoiImg(cv::String filename)
{
	if (RoiImg.empty())
	{
		std::cout << "ROI image is empty! \nPlease read a image and draw ROI!" << std::endl;
		return false;
	}

	try
	{
		size_t ExtDotPos = filename.find_last_of(".");
		cv::String Ext = filename.substr(ExtDotPos + 1, filename.length() - ExtDotPos);

		// §PÂ_¬O§_¬°jpg
		if (Ext.compare("bmp") == 0)
			cv::imwrite(filename, RoiImg);
		else if (Ext.compare("jpg") == 0 || Ext.compare("jpeg") == 0)
		{
			/*std::vector<int> quality;
			quality.push_back(cv::IMWRITE_JPEG_QUALITY);
			quality.push_back(90);
			cv::imwrite(filename, RoiImg, quality);*/
			cv::imwrite(filename, RoiImg);
		}
		else if (Ext.compare("png") == 0)
		{
			std::vector<int> compression_params;
			compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
			compression_params.push_back(3);
			cv::Mat BeSaved;
			BeSaved.create(RoiImg.size(), CV_8UC4);
			cv::cvtColor(RoiImg, BeSaved, CV_RGB2RGBA);
			cv::imwrite(filename, BeSaved, compression_params);
			BeSaved.release();
		}
		else
			std::cout << "Only support bmp and jpg, png. \nPlease re-input!" << std::endl;

		return true;
	}
	catch (cv::Exception err)
	{
		std::cout << err.what() << std::endl;
		return false;
	}
}