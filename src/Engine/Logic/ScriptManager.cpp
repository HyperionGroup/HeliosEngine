#include "Logic.h"

#include "ScriptManager.h"

#include "Logger\Logger.h"

#include "Str.h"

namespace logic
{

  CScriptManager::CScriptManager()
  {
    mLuaState.open_libraries(sol::lib::base, sol::lib::jit);

    //TODO: MOVE (To specific binding cpp file)

    mLuaState["log_info"] = [](std::string str) { LOG_INFO_APPLICATION(str.c_str()); };
    mLuaState["log_warning"] = [](std::string str) { LOG_WARNING_APPLICATION(str.c_str()); };
    mLuaState["log_error"] = [](std::string str) { LOG_ERROR_APPLICATION(str.c_str()); };

    sol::constructors<core::CStr(const std::string&), core::CStr(const char*)> ctor;
    sol::usertype<core::CStr> CStrLuaType(ctor, "cpp_type", []() { return typeid(core::CStr).name(); }, "is_empty", &core::CStr::IsEmpty, "raw", &core::CStr::ToCStr);
    mLuaState.set_usertype("cstr", CStrLuaType);

  }

}