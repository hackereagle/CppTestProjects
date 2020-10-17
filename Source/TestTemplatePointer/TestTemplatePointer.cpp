// TestTemplatePointer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

// refer to https://stackoverflow.com/questions/2448242/struct-with-template-variables-in-c
// http://rocksaying.tw/archives/3641717.html

template<typename T>
struct image
{
	int num;
	T* data;
};
//typedef struct image<T> Image;

int main()
{
	image<int> A;
	A.num = 3;
	A.data = new int[A.num]{ 1, 2, 3 };

	image<double> B;
	B.num = 3;
	B.data = new double[B.num]{1.0, 2.0, 30.0};

	std::cout << "image size = " << sizeof(B) << std::endl;
	std::cout << "A size = " << sizeof(A) << "\n\tdata = " << A.data[0] << ", " << A.data[1] << ", " << A.data[2] << std::endl;
	std::cout << "B size = " << sizeof(B) << "\n\tdata = " << B.data[0] << ", " << B.data[1] << ", " << B.data[2] << std::endl;

	std::cout << "get type size of template implement int* = " << sizeof(A.data) << std::endl;
	std::cout << "real int* size = " << sizeof(int*) << std::endl;
	std::cout << "get type size of template implement double* = " << sizeof(B.data) << std::endl;
	std::cout << "real double* size = " << sizeof(double*) << std::endl;

	system("pause");
    return 0;
}

