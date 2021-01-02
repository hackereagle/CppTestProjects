#ifndef _RORZE_LOGGER_H_
#define _RORZE_LOGGER_H_ 


class Logger
{
public:
    static Logger *GetInsance();
    ~Logger();
    void AsyncWrite(char *msg);

private:
    Logger();
    static Logger *mInstance;

};
 #endif //_RORZE_LOGGER_H_