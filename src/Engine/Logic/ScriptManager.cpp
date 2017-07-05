#include "Logic.h"

#include "ScriptManager.h"

#include "Logger\Logger.h"

namespace logic
{

  CScriptManager::CScriptManager()
  {
    mLuaState.open_libraries(sol::lib::base, sol::lib::jit);
    mLuaState["script_print"] = [](std::string str){ LOG_INFO_APPLICATION(str.c_str()); };
  }

}