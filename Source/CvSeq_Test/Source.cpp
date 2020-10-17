#include <opencv2\opencv.hpp>
#include <io.h>
#include <fstream>

using namespace cv;
using namespace std;

void main()
{
	IplImage *img = cvLoadImage("polygonImg.bmp", CV_LOAD_IMAGE_GRAYSCALE);

	IplImage *Region = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
	cvThreshold(img, Region, 50, 255, CV_THRESH_BINARY_INV);

	cvNamedWindow("original img", CV_WINDOW_NORMAL);
	cvShowImage("original img", Region);
	cvWaitKey(0);
	cvDestroyAllWindows();

	fstream fp;
	fp.open("PointAndInformationOfContour.txt", ios::out|ios::app);

	CvMemStorage *pcvMStorage = cvCreateMemStorage();
	CvSeq *contours = NULL;
	int NumOfContour = cvFindContours(Region, pcvMStorage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, cvPoint(0, 0)); 
	cout << "Total number of contours = " << NumOfContour << endl;

	IplImage *contoursImg = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);
	cvZero(contoursImg);
	for (int i = 0; (contours != NULL); contours = contours->h_next)
	{
		fp << "-----------------" << i + 1 << "-th contour/CvSeq information-----------------------------" << endl;
		fp << "CvSeq->total = " << contours->total << endl;
		fp << "All points:" << endl;
		int count = contours->total;
		CvPoint center;
		CvSize size;

		CvPoint *PointArray = (CvPoint*)malloc(count * sizeof(CvPoint));
		CvPoint2D32f *PointArray2D32f = (CvPoint2D32f*)malloc(count * sizeof(CvPoint2D32f));
		cvCvtSeqToArray(contours, PointArray, CV_WHOLE_SEQ);
		for (int j = 0; j < count; j++)
		{
			PointArray2D32f[j].x = (float)PointArray[j].x;
			PointArray2D32f[j].y = (float)PointArray[j].y;
			fp << "point " << j << ":(" << PointArray2D32f[j].x << ", " << PointArray2D32f[j].y << ")" << endl;
		}
		cvDrawContours(contoursImg, contours, CV_RGB(255, 0, 0), CV_RGB(0, 0, 100), 1, 2, 8, cvPoint(0, 0));
	}

	cvNamedWindow("contour", 0);
	cvShowImage("contour", contoursImg);
	cvWaitKey(0);
	cvDestroyWindow("contour");

	// Using polygon to approximate each contours
	fp << "//------------------------------------------- contour approximate polygon----------------------------------------------//" << endl;
	IplImage *polygonImg = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);
	CvSeq *contoursApproxPoly;
	CvSeq *EachContour;
	CvMemStorage *ApproxPolyStorage = NULL;

	int i = 0;
	CvTreeNodeIterator iterator;
	cvInitTreeNodeIterator(&iterator, contours, 1);
	while (0 != (EachContour = (CvSeq*)cvNextTreeNode(&iterator)))
	{
		contoursApproxPoly = cvApproxPoly((void*)EachContour, sizeof(CvContour), ApproxPolyStorage, CV_POLY_APPROX_DP, cvContourPerimeter(EachContour) * 0.02, 0);
		//contoursApproxPoly = cvApproxPoly((void*)EachContour, sizeof(CvContour), ApproxPolyStorage, CV_POLY_APPROX_DP, cvArcLength(contours) * 0.02, 0);

		fp << "-----------------" << i + 1 << "-th contour approx polygon/CvSeq information-----------------------------" << endl;
		fp << "CvSeq->total = " << EachContour->total << endl;
		fp << "All points:" << endl;
		int count = EachContour->total;

		CvPoint *PointArray = (CvPoint*)malloc(count * sizeof(CvPoint));
		CvPoint2D32f *PointArray2D32f = (CvPoint2D32f*)malloc(count * sizeof(CvPoint2D32f));
		cvCvtSeqToArray(contoursApproxPoly, PointArray, CV_WHOLE_SEQ);
		for (int j = 0; j < NumOfContour; j++)
		{
			PointArray2D32f[j].x = (float)PointArray[j].x;
			PointArray2D32f[j].y = (float)PointArray[j].y;
			fp << "point " << j << ":(" << PointArray2D32f[j].x << ", " << PointArray2D32f[j].y << ")" << endl;
		}
		cvDrawContours(polygonImg, contoursApproxPoly, CV_RGB(255, 0, 0), CV_RGB(0, 0, 100), 1, 2, 8, cvPoint(0, 0));
	}

	cvNamedWindow("approximate polygon", 0);
	cvShowImage("approximate polygon", polygonImg);
	cvWaitKey(0);
	cvDestroyWindow("approximate polygon");
}