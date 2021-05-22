#include <string>
#include <iostream>
#include <fstream>
#include <mutex>
#include <chrono>
#include <sys/stat.h>
#include <filesystem>
#include <utility>
#include "Logger.h"

Logger* Logger::mInstance = nullptr;
std::mutex obj;

Logger::Logger()
{
    std::string env = getenv("HOME");
    this->mLogPath = env +  std::string("/Logs");
    std::cout << this->mLogPath << std::endl;
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

bool Logger::Initialize(LogLevel fileLogLevel)
{
    bool isSucess = false;

    this->mLevel = fileLogLevel;
    if(this->mIsInitialize == false){
        this->mIsInitialize = true;
        mIsAsyncWrite = true;
        mBackgroundWriteLog = std::thread(&Logger::AsyncWriteLogService, this);

        isSucess = true;
    }

    return isSucess;
}

void Logger::CheckDirectoryExist(std::string& path)
{
    std::filesystem::path dir(path);
    bool isExist = std::filesystem::exists(dir);
    if(!isExist) {
        std::filesystem::create_directories(dir);
    }
}

void Logger::WriteToFile(std::unique_ptr<LogArgs> log)
{
    if(log->GetLevel() >= this->mLevel){
        std::string path = this->mLogPath + mPathSpacer + log->GetLogDate() + mPathSpacer + EnumToString(log->GetType()) + mPathSpacer;
        std::string filename = EnumToString(log->GetType()) + log->GetLogHour() + ".log";
        std::string logFile = path + filename;

        std::fstream fileStream;
        std::filesystem::path logFilePath(logFilePath);
        if(std::filesystem::exists(logFilePath)) {
            fileStream.open(logFile, std::ios::out | std::ios::app);
        }
        else{
            CheckDirectoryExist(path);
            fileStream.open(logFile, std::ios::out | std::ios::app);
        }
        
        fileStream << log->GetLogTime() << "\t" << log->GetActionMessage() << std::endl;
        fileStream.close();
        // std::cout << log->GetActionMessage() << std::endl;
    }
}

void Logger::AsyncWriteLogService()
{
    if(!mIsInitialize) {
        throw new std::exception();
    }

    while (mIsAsyncWrite || this->mLogBuffer.size() > 0) {
        if(mLogBuffer.size() > 0){
            std::unique_ptr<LogArgs> _log = std::move(mLogBuffer.front());
            mLogBuffer.pop();

            WriteToFile(std::move(_log));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(this->mWritePeriod));
    }
}

void Logger::AsyncWrite(LogType type, const char *msg, LogLevel level, std::shared_ptr<DateTime> time)
{
    if(!mIsInitialize) {
        printf("Not initialize Logger!");
        throw std::exception();
    }

    this->mLogBuffer.push(std::make_unique<LogArgs>(type, msg, level, time));
}

void Logger::AsyncWrite(LogType type, std::string msg, LogLevel level, std::shared_ptr<DateTime> time)
{
    if(!mIsInitialize) {
        printf("Not initialize Logger!");
        throw std::exception();
    }

    this->mLogBuffer.push(std::make_unique<LogArgs>(type, msg.c_str(), level, time));
}

void Logger::RestarAsyncWrite()
{
    if(!mBackgroundWriteLog.joinable() || mIsAsyncWrite == false){
        mIsAsyncWrite = true;
        mBackgroundWriteLog = std::thread(&Logger::AsyncWriteLogService, this);
    }
}

void Logger::StopAsyncWrite()
{
    mIsAsyncWrite = false;
}