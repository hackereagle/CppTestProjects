#ifndef _LOG_ARGS_H_
#define _LOG_ARGS_H_

#include <iostream>
#include <memory>
#include <string>
#include "LoggerCommon.h"
#include "DateTime.h"

class LogArgs
{
public:
    LogArgs(LogType type, const char* msg, LogLevel level = LogLevel::LOGINFO, std::shared_ptr<DateTime> time = nullptr)
    {
        mLevel = level;
        mType = type;
        mActionMessage = msg;
        if(time == nullptr)
            mTime = std::make_shared<DateTime>();
    }

    ~LogArgs(){
        // test
        std::cout << "LogArgs be deleted!" << std::endl;
    }
    std::string GetTime(){
        std::string time;
        try{
            std::ostringstream ss;
            ss << mTime->GetYear()
               << "." << std::setfill('0') << std::setw(2) << mTime->GetMonth()
               << "." << std::setfill('0') << std::setw(2) << mTime->GetDay()
               << " " << std::setfill('0') << std::setw(2) << mTime->GetHour()
               << ":" << std::setfill('0') << std::setw(2) << mTime->GetMinute()
               << ":" << std::setfill('0') << std::setw(2) << mTime->GetSecond()
               << "." << std::setfill('0') << std::setw(2) << mTime->GetMillisecond() << std::endl;
            time = ss.str();
        }
        catch(std::exception ex){
            std::cout << "In LogArgs occur ERROR: " << ex.what() << std::endl;
        }
        return time;
    }
    LogType GetType(){ return mType;}
    LogLevel GetLevel(){ return mLevel;}
    const char* GetActionMessage(){ return mActionMessage;}

private:
    const char* mActionMessage; 
    LogLevel mLevel;
    LogType mType;
    std::shared_ptr<DateTime> mTime;
};

#endif // _LOG_ARGS_H_