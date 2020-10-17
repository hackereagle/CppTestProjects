#include <opencv2\opencv.hpp>
#include "DrawRoi.h"

using namespace cv;
using namespace std;

// test opencv mouse event
// by http://monkeycoding.com/?p=653 
/*cv::Point VertexLeftTop = cv::Point(-1, -1);
cv::Point VertexRightdown = cv::Point(-1, -1);
cv::Point tempVertexRightdown = cv::Point(-1, -1);

void onMouse(int Event, int x, int y, int flag, void* param)
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
}

void main()
{
	Mat srcImg = imread("D:\\hacker station of SC\\project\\OpenHalcon\\dll test\\lena.bmp", CV_LOAD_IMAGE_COLOR);

	namedWindow("test", CV_WINDOW_NORMAL);
	imshow("test", srcImg);
	//waitKey(0);
	cv::setMouseCallback("test", onMouse, NULL);

	while (true)
	{
		if (VertexLeftTop.x == -1 && VertexRightdown.x == -1)
			cv::imshow("test", srcImg);

		if (VertexLeftTop.x != -1 && VertexRightdown.x != -1)
		{
			rectangle(srcImg, cv::Rect(VertexLeftTop, VertexRightdown), cv::Scalar(0, 0, 255), 2);
			VertexLeftTop = cv::Point(-1, -1);
			VertexRightdown = cv::Point(-1, -1);
			cv::imshow("test", srcImg);
		}

		if (VertexLeftTop.x != -1 && tempVertexRightdown.x != -1)
		{
			cv::Mat tempImg = srcImg.clone();
			rectangle(tempImg, cv::Rect(VertexLeftTop, tempVertexRightdown), cv::Scalar(0, 0, 255), 2);
			cv::imshow("test", tempImg);
		}

		if (cvWaitKey(33) == 27)
			break;
	}
}
*/

// test drawing ROI class and its method.
void main()
{
	Mat srcImg = imread("D:\\Document\\program\\00.TestAndLearning\\Test\\MouseEventTest\\MouseEventTest\\lena.bmp", CV_LOAD_IMAGE_COLOR);
	//Mat srcImg = imread("D:\\hacker station of SC\\project\\OpenHalcon\\dll test\\lena.bmp", CV_LOAD_IMAGE_GRAYSCALE);

	namedWindow("test", CV_WINDOW_NORMAL);
	imshow("test", srcImg);
	//waitKey(0);
	
	DrawRoi *_DrawRoi = new DrawRoi();
	_DrawRoi->DrawRectangle("test", srcImg);
	//_DrawRoi->DrawCircle("test", srcImg);
	_DrawRoi->showRoiImage();
	_DrawRoi->SaveRoiImg("test.jpg");

	cout << "<<<<<<<<<<<<<<< ROI Information >>>>>>>>>>>>>>>" << endl;
	cout << "ROI left top point:\n\t x = " << _DrawRoi->RoiInformation.LeftTopPoint.x << "\n\t y = " << _DrawRoi->RoiInformation.LeftTopPoint.y << endl;
	cout << "ROI size:\n\t width = " << _DrawRoi->RoiInformation.width << "\n\t height = " << _DrawRoi->RoiInformation.height << endl;
	cout << "ROI center:\n\t x = " << _DrawRoi->RoiInformation.center.x << "\n\t y = " << _DrawRoi->RoiInformation.center.y << endl;
	system("pause");
}

