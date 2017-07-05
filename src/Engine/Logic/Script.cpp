#include "Logic.h"

#include "Script.h"

#include "Engine/Engine.h"

#include "ScriptManager.h"

namespace logic
{

  CScript::CScript( std::string aCode )
  {
    sol::environment env(LUA_STATE, sol::create, LUA_STATE.globals() );
    mEnv = env;
    LUA_STATE.script( aCode, mEnv );
  }

  void CScript::operator[](std::string aName)
  {
    mEnv[aName];
  }

}