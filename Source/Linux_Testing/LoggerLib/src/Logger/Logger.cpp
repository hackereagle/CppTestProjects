#include "Logger.h"
#include <string>
#include <iostream>

Logger::Logger()
{

}

Logger::~Logger()
{

}

Logger *Logger::GetInsance()
{
    if(Logger::mInstance == nullptr){
        Logger::mInstance = new Logger();
    }

    return Logger::mInstance;
}

void Logger::AsyncWrite(char* msg)
{
    std::cout << std::string(msg) << std::endl;
}