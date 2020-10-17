#include <opencv2\opencv.hpp>

int main()
{
	cv::Mat srcImg = cv::imread("test.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	cv::namedWindow("test", CV_WINDOW_NORMAL);
	cv::imshow("test", srcImg);
	cv::waitKey(0);
	cv::Mat output;
	cv::resize(srcImg, output, cv::Size(512, 1024));
	//cv::imwrite("save2.bmp", output);

	cv::Mat padded;
	//int m = cv::getOptimalDFTSize(srcImg.rows);  //m為大於等於srcImg.rows裡的最小值，且須為2、3、5的次方相乘
	//int n = cv::getOptimalDFTSize(srcImg.cols);
	int m = 2048;  //m為大於等於srcImg.rows裡的最小值，且須為2、3、5的次方相乘
	int n = 1024;
	cv::copyMakeBorder(srcImg, padded, 0, m - srcImg.rows, 0, n - srcImg.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0)); //為了效率，所以對影像邊界拓展
	cv::imwrite("save.bmp", padded);

	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	cv::Mat complexImg;
	cv::merge(planes, 2, complexImg);
	cv::dft(complexImg, complexImg);

	cv::split(complexImg, planes);                  //分離通道，planes[0]為實數部分，planes[1]為虛數部分 
	cv::magnitude(planes[0], planes[1], planes[0]); //planes[0] = sqrt((planes[0])^2 + (planes[1])^2
	cv::Mat magI = planes[0];
	magI += cv::Scalar::all(1);                     //magI = log(1+planes[0])
	cv::log(magI, magI);

	magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));  //令邊長為偶數

															  //將區塊重排，讓原點在影像的中央
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));
	cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));
	cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));
	cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy));

	cv::Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	cv::normalize(magI, magI, 0, 1, CV_MINMAX);

	cv::imshow("輸入圖", srcImg);
	cv::imshow("頻譜", magI);

	//逆向傅立葉轉換
	cv::Mat ifft;
	cv::idft(complexImg, ifft, cv::DFT_REAL_OUTPUT);
	cv::normalize(ifft, ifft, 0, 1, CV_MINMAX);
	cv::imshow("逆向求輸入圖", ifft);
	cv::waitKey();

	return 0;
}