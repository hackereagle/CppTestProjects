#include "RorzeLogger.h"

RorzeLogger::RorzeLogger()
{

}

RorzeLogger::~RorzeLogger()
{

}

RorzeLogger *RorzeLogger::GetInsance()
{
    if(RorzeLogger::mInstance == nullptr){
        RorzeLogger::mInstance = new RorzeLogger();
    }

    return RorzeLogger::mInstance;
}