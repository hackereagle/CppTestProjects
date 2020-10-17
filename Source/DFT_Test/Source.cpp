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
	//int m = cv::getOptimalDFTSize(srcImg.rows);  //m���j�󵥩�srcImg.rows�̪��̤p�ȡA�B����2�B3�B5������ۭ�
	//int n = cv::getOptimalDFTSize(srcImg.cols);
	int m = 2048;  //m���j�󵥩�srcImg.rows�̪��̤p�ȡA�B����2�B3�B5������ۭ�
	int n = 1024;
	cv::copyMakeBorder(srcImg, padded, 0, m - srcImg.rows, 0, n - srcImg.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0)); //���F�Ĳv�A�ҥH��v����ɩݮi
	cv::imwrite("save.bmp", padded);

	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	cv::Mat complexImg;
	cv::merge(planes, 2, complexImg);
	cv::dft(complexImg, complexImg);

	cv::split(complexImg, planes);                  //�����q�D�Aplanes[0]����Ƴ����Aplanes[1]����Ƴ��� 
	cv::magnitude(planes[0], planes[1], planes[0]); //planes[0] = sqrt((planes[0])^2 + (planes[1])^2
	cv::Mat magI = planes[0];
	magI += cv::Scalar::all(1);                     //magI = log(1+planes[0])
	cv::log(magI, magI);

	magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));  //�O���������

															  //�N�϶����ơA�����I�b�v��������
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

	cv::imshow("��J��", srcImg);
	cv::imshow("�W��", magI);

	//�f�V�ť߸��ഫ
	cv::Mat ifft;
	cv::idft(complexImg, ifft, cv::DFT_REAL_OUTPUT);
	cv::normalize(ifft, ifft, 0, 1, CV_MINMAX);
	cv::imshow("�f�V�D��J��", ifft);
	cv::waitKey();

	return 0;
}