#ifndef _RORZE_LOGGER_H_
#define _RORZE_LOGGER_H_ 

#include "../include/ILogger.h"

class RorzeLogger
{
public:
    static RorzeLogger *GetInsance();
    ~RorzeLogger();
    void AsyncWrite(char *msg);

private:
    RorzeLogger();
    static RorzeLogger *mInstance;

};
 #endif //_RORZE_LOGGER_H_