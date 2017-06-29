#include "Core.h"

#include "Logger.h"
#include "Name.h"

Begin_Enum_String(core::CLogger::ELogLevel)
{
    Enum_String_Id(core::CLogger::eLogInfo, "Info");
    Enum_String_Id(core::CLogger::eLogWarning, "Warning");
    Enum_String_Id(core::CLogger::eLogError, "Error");
}
End_Enum_String;

namespace core 
{
    void CLogger::AddNewLog(ELogLevel aLevel, const char* fmt, ...)
    {
        std::string lTag = "[" + EnumString<ELogLevel>::ToStr(aLevel) + "]";
        va_list args;
        char* buffer;
        va_start(args, fmt);
        int len = _vscprintf(fmt, args) + 1;
        buffer = (char*)malloc(len * sizeof(char));
        vsprintf_s(buffer, len, fmt, args);
        std::string output = lTag + buffer;
        free(buffer);
        va_end(args);
        OutputDebugString(output.c_str());
    }
}
