#pragma once
#ifndef _H_DRAW_ROI
#include <opencv2\opencv.hpp>

class DrawRoi
{
public:
	DrawRoi();
	~DrawRoi();
	enum enumRoiType
	{
		RECTANGLE,
		CIRCLE
		// in feture, can draw ellipse and polygon ROI.
	};

	typedef struct
	{
		cv::Point LeftTopPoint;
		int width;
		int height;
		cv::Point center;
		int type;
	}Roi;
	Roi RoiInformation;
	cv::Mat RoiImg;
	void DrawRectangle(cv::String WindowsName, cv::Mat srcImg);
	void DrawCircle(cv::String WindowsName, cv::Mat srcImg);
	void showRoiImage();
	void setDrawColor(cv::Scalar color);

private:
	cv::Scalar _color;
	cv::Point VertexLeftTop = cv::Point(-1, -1);
	cv::Point VertexRightdown = cv::Point(-1, -1);
	cv::Point tempVertexRightdown = cv::Point(-1, -1);
	static void onMouse(int Event, int x, int y, int flag, void* param);
	void MouseEven(int Event, int x, int y, int flag);
	int MouseStatu();
	enum enumMouseStatu
	{
		MouseNoActivity,
		MouseHaul,
		FinishingRoi,
		EndDraw
	};
};

#endif // !_H_DRAW_ROI


