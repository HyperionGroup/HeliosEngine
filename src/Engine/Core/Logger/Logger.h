#pragma once
#ifndef __H_LOGGER__
#define __H_LOGGER__

#include "Singleton.h"

#include <vector>
#include <string>

#ifdef NO_LOGS
#define LOG_ERROR_APPLICATION( x, ... ){}
#define LOG_WARNING_APPLICATION( x, ...  ){}
#define LOG_INFO_APPLICATION( x, ...  ){}
#else 
#define LOG_ERROR_APPLICATION( x, ... )     core::CLogger::GetInstance().AddNewLog( core::CLogger::eLogError,   x, __VA_ARGS__ )
#define LOG_WARNING_APPLICATION( x, ...  )  core::CLogger::GetInstance().AddNewLog( core::CLogger::eLogWarning, x, __VA_ARGS__ )
#define LOG_INFO_APPLICATION( x, ...  )     core::CLogger::GetInstance().AddNewLog( core::CLogger::eLogInfo,    x, __VA_ARGS__ )
#define LOG_ERROR_APPLICATION_IF( condition, x, ... ) if(condition) core::CLogger::GetInstance().AddNewLog( core::CLogger::eLogError,   x, __VA_ARGS__ )
#endif

namespace core
{
    class CLogger : public CSingleton<CLogger>
    {
    public:
        enum ELogLevel
        {
            eLogInfo = 0,
            eLogWarning,
            eLogError
        };
    public:
        CLogger() {}
        virtual ~CLogger() {}
        void AddNewLog(ELogLevel aLevel, const char* fmt, ...);
    };
}

#endif // __H_LOGGER__