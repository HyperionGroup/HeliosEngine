#pragma once

#include <sol.hpp>

namespace logic
{
  class CScriptManager
  {
  public:
    CScriptManager();
    ~CScriptManager();

    sol::state mLuaState;
  };
}

#define LUA_STATE helios::CEngine::GetInstance().GetScriptManager().mLuaState