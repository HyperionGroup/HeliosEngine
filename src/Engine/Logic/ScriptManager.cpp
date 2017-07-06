#include "Logic.h"

#include "ScriptManager.h"

#include "Logger\Logger.h"

namespace logic
{

  CScriptManager::CScriptManager()
  {
    mLuaState.open_libraries(sol::lib::base, sol::lib::jit);

    mLuaState["log_info"] = [](std::string str) { LOG_INFO_APPLICATION(str.c_str()); };
    mLuaState["log_warning"] = [](std::string str) { LOG_WARNING_APPLICATION(str.c_str()); };
    mLuaState["log_error"] = [](std::string str) { LOG_ERROR_APPLICATION(str.c_str()); };
  }

}