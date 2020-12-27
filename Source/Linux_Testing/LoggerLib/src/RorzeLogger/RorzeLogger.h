#ifndef _RORZE_LOGGER_H_
#define _RORZE_LOGGER_H_ 

class RorzeLogger
{
public:
    static RorzeLogger *GetInsance();
    ~RorzeLogger();

private:
    RorzeLogger();
    static RorzeLogger *mInstance = nullptr;

};
 #endif //_RORZE_LOGGER_H_