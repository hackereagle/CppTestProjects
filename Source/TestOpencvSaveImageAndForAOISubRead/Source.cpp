#include "opencv2\opencv.hpp"

using namespace cv;
using namespace std;

bool SaveIplimage2Bmp(IplImage* BeSavedImg, const char* fileName)
{
	string tempFileName(fileName), file;
	std::size_t onlyHaveFileName = tempFileName.find("\\");
	if (onlyHaveFileName == std::string::npos)
		file = "\\" + tempFileName;
	else
		file = tempFileName;

	cvSaveImage(tempFileName.c_str(), BeSavedImg);

	// open the bmp file
	FILE *bmpStream;
	bmpStream = fopen(file.c_str(), "rb");
	if (!bmpStream)
	{
		printf("File is not exist?\n");
		return false;
	}
	unsigned char *buff = new unsigned char[54];
	size_t rlen = fread((void*)buff, sizeof(unsigned char), 54, bmpStream);

	// check the file whether is bmp file
	if ((buff[0] != 'B') | (buff[1] != 'M') | (rlen != 54))
	{
		delete[] buff;
		fclose(bmpStream);
		printf("The File is Not Correct Format.\n");
		return false;
	}

	long bmpWidth = *(long*)&buff[18];
	long bmpHeight = *(long*)&buff[22];
	long bmpDataSize = *(long*)&buff[34];
	long bmpDataShift = *(long*)&buff[10];
	if (fseek(bmpStream, bmpDataShift, SEEK_SET) != 0)
	{
		delete[] buff;
		fclose(bmpStream);
		return false;
	}

	if (bmpDataSize == 0)
		bmpDataSize = bmpWidth * bmpHeight;
	else
		return true;
	fclose(bmpStream);

	// if haven't bmpDataSize resave bmp file
	int rem = bmpWidth % 4;
	bmpWidth -= rem;

	unsigned char header[54];
	memset(&header[0], 0, 54);
	header[0] = 'B';
	header[1] = 'M';
	long tempL = (bmpWidth) * (bmpHeight) + (1078);
	//避免overflow
	size_t tempL64 = static_cast<size_t>(bmpWidth) * static_cast<size_t>(bmpHeight) + 1078;
	if ((size_t)tempL != tempL64)
	{
		printf("The Image is Too Large to Save. \n");
		return false;
	}

	//製作標頭檔
	memcpy(&header[2], &tempL, sizeof(long));
	tempL = 1078;
	memcpy(&header[10], &tempL, sizeof(long));
	tempL = 40;
	memcpy(&header[14], &tempL, sizeof(long));
	tempL = bmpWidth;
	memcpy(&header[18], &tempL, sizeof(long));
	tempL = bmpHeight;
	memcpy(&header[22], &tempL, sizeof(long));
	short tempS = 1;
	memcpy(&header[26], &tempS, sizeof(short));
	tempS = 8;
	memcpy(&header[28], &tempS, sizeof(short));
	tempL = 0;
	memcpy(&header[30], &tempL, sizeof(long));
	tempL = bmpDataSize;
	memcpy(&header[34], &tempL, sizeof(long));
	tempL = 0;
	memcpy(&header[38], &tempL, sizeof(long));
	tempL = 0;
	memcpy(&header[42], &tempL, sizeof(long));
	tempL = 0;
	memcpy(&header[46], &tempL, sizeof(long));
	tempL = 0;
	memcpy(&header[50], &tempL, sizeof(long));

	//填寫調色盤
	unsigned char Palette[1024];
	memset(&Palette[0], 0, 1024);
	for (int i = 0; i<256; i++)
	{
		Palette[i * 4 + 0] = i;
		Palette[i * 4 + 1] = i;
		Palette[i * 4 + 2] = i;
		Palette[i * 4 + 3] = 0;
	}

	//將標頭檔、調色盤、bmpdata寫入
	//FILE *bmpStream;
	bmpStream = fopen(file.c_str(), "wb");
	if (!bmpStream)
		return false;
	size_t wlen = fwrite(&header[0], sizeof(unsigned char), 54, bmpStream);
	if (wlen != 54)
		return false;
	wlen = fwrite(&Palette[0], sizeof(unsigned char), 1024, bmpStream);
	if (wlen != 1024)
		return false;

	rem = (bmpWidth % 4 == 0) ? 0 : 4 - (bmpWidth % 4);
	if (rem == 0)	//基本上 rem 一定等於零 因為之前有做過修正
	{
		for (int i = bmpHeight - 1; i >= 0; i--)
		{
			wlen = fwrite(&BeSavedImg->imageData[static_cast<size_t>(i) * static_cast<size_t>(BeSavedImg->width)], sizeof(unsigned char), static_cast<size_t>(bmpWidth), bmpStream);
		}
	}
	else
	{
		fclose(bmpStream);
		return false;
	}

	fclose(bmpStream);

	return true;
}

bool SaveMat2Bmp(Mat BeSavedImg, const char* fileName)
{
	string tempFileName(fileName), file;
	std::size_t onlyHaveFileName = tempFileName.find("\\");
	if (onlyHaveFileName == std::string::npos)
		file = "\\" + tempFileName;
	else
		file = tempFileName;

	imwrite(file, BeSavedImg);

	// open the bmp file
	FILE *bmpStream;
	bmpStream = fopen(file.c_str(), "rb");
	if (!bmpStream)
	{
		printf("File is not exist?\n");
		return false;
	}
	unsigned char *buff = new unsigned char[54];
	size_t rlen = fread((void*)buff, sizeof(unsigned char), 54, bmpStream);

	// check the file whether is bmp file
	if ((buff[0] != 'B') | (buff[1] != 'M') | (rlen != 54))
	{
		delete[] buff;
		fclose(bmpStream);
		printf("The File is Not Correct Format.\n");
		return false;
	}

	long bmpWidth = *(long*)&buff[18];
	long bmpHeight = *(long*)&buff[22];
	long bmpDataSize = *(long*)&buff[34];
	long bmpDataShift = *(long*)&buff[10];
	if (fseek(bmpStream, bmpDataShift, SEEK_SET) != 0)
	{
		delete[] buff;
		fclose(bmpStream);
		return false;
	}

	if (bmpDataSize == 0)
		bmpDataSize = bmpWidth * bmpHeight;
	else
		return true;
	fclose(bmpStream);

	// if haven't bmpDataSize resave bmp file
	int rem = bmpWidth % 4;
	bmpWidth -= rem;

	unsigned char header[54];
	memset(&header[0], 0, 54);
	header[0] = 'B';
	header[1] = 'M';
	long tempL = (bmpWidth) * (bmpHeight)+(1078);
	//避免overflow
	size_t tempL64 = static_cast<size_t>(bmpWidth) * static_cast<size_t>(bmpHeight) + 1078;
	if ((size_t)tempL != tempL64)
	{
		printf("The Image is Too Large to Save. \n");
		return false;
	}

	//製作標頭檔
	memcpy(&header[2], &tempL, sizeof(long));
	tempL = 1078;
	memcpy(&header[10], &tempL, sizeof(long));
	tempL = 40;
	memcpy(&header[14], &tempL, sizeof(long));
	tempL = bmpWidth;
	memcpy(&header[18], &tempL, sizeof(long));
	tempL = bmpHeight;
	memcpy(&header[22], &tempL, sizeof(long));
	short tempS = 1;
	memcpy(&header[26], &tempS, sizeof(short));
	tempS = 8;
	memcpy(&header[28], &tempS, sizeof(short));
	tempL = 0;
	memcpy(&header[30], &tempL, sizeof(long));
	tempL = bmpDataSize;
	memcpy(&header[34], &tempL, sizeof(long));
	tempL = 0;
	memcpy(&header[38], &tempL, sizeof(long));
	tempL = 0;
	memcpy(&header[42], &tempL, sizeof(long));
	tempL = 0;
	memcpy(&header[46], &tempL, sizeof(long));
	tempL = 0;
	memcpy(&header[50], &tempL, sizeof(long));

	//填寫調色盤
	unsigned char Palette[1024];
	memset(&Palette[0], 0, 1024);
	for (int i = 0; i<256; i++)
	{
		Palette[i * 4 + 0] = i;
		Palette[i * 4 + 1] = i;
		Palette[i * 4 + 2] = i;
		Palette[i * 4 + 3] = 0;
	}

	//將標頭檔、調色盤、bmpdata寫入
	//FILE *bmpStream;
	bmpStream = fopen(file.c_str(), "wb");
	if (!bmpStream)
		return false;
	size_t wlen = fwrite(&header[0], sizeof(unsigned char), 54, bmpStream);
	if (wlen != 54)
		return false;
	wlen = fwrite(&Palette[0], sizeof(unsigned char), 1024, bmpStream);
	if (wlen != 1024)
		return false;

	rem = (bmpWidth % 4 == 0) ? 0 : 4 - (bmpWidth % 4);
	if (rem == 0)	//基本上 rem 一定等於零 因為之前有做過修正
	{
		for (int i = bmpHeight - 1; i >= 0; i--)
		{
			wlen = fwrite(&BeSavedImg.data[static_cast<size_t>(i) * static_cast<size_t>(BeSavedImg.cols)], sizeof(unsigned char), static_cast<size_t>(bmpWidth), bmpStream);
		}
	}
	else
	{
		fclose(bmpStream);
		return false;
	}

	fclose(bmpStream);

	return true;
}

void main()
{
	string path = "D:\\Document\\program\\02.玻璃缺陷檢測\\樣品\\";
	string inputfile = "3.2um_pi_bercheck.bmp";
	string file = path + inputfile;

	/*Mat MatImg;
	MatImg = imread(file.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
	file = path + "MatImg.bmp";
	imwrite(file, MatImg);*/

	IplImage *IplImg;
	IplImg = cvLoadImage(file.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
	file = path + "IplImg.bmp";
	cvSaveImage(file.c_str(), IplImg);

	SaveIplimage2Bmp(IplImg, "IplImg_new.bmp");
}