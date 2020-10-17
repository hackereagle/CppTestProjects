#pragma once
#include "Common_Parameters.h"

typedef void ResultType;

class IAlgorithm
{
public:
	virtual ~IAlgorithm() { ; }
	virtual int inspect(const ImageParam imgParam, char* inputParams, char** outputParam) = 0;
	virtual int getResult(char* Type, int* Num, ResultType** Ret) = 0; // for sub to get calculate result.
	virtual int releaseResult(ResultType** Ret) = 0; // for sub to get release result.

protected:

};

