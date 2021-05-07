#include <string>
#include <iostream>
#include <mutex>
#include <chrono>
#include "Logger.h"

Logger* Logger::mInstance = nullptr;
std::mutex obj;

Logger::Logger()
{

}

Logger::~Logger()
{

}

Logger& Logger::GetInsance()
{
    std::lock_guard<std::mutex> lock(obj);
    if(Logger::mInstance == nullptr){
        Logger::mInstance = new Logger();
    }

    return *Logger::mInstance;
}

bool Logger::Initialize(LogLevel fileLogLevel = LogLevel::LOGINFO)
{
    bool isSucess = false;

    this->mLevel = fileLogLevel;
    isSucess = true;

    return isSucess;
}

void Logger::AsyncWrite(char* msg)
{
    std::cout << std::string(msg) << std::endl;
    // mLofBuffer.push
}

void Logger::AsyncWriteLogService()
{
    if(!mIsInitialize) {
        throw new std::exception();
    }

    while (mIsAsyncWrite || this->mLogBuffer.size() > 0) {
        if(mLogBuffer.size() > 0){
            // TODO: write to file
            // mLogBuffer.pop
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(this->mWritePeriod));
    }
    
}