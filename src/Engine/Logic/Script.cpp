#include "Logic.h"

#include "Script.h"

#include "Engine/Engine.h"

#include "ScriptManager.h"

namespace logic
{

  CScript::CScript( std::string aCode )
  {
    mEnv = new sol::environment(LUA_STATE, sol::create, LUA_STATE.globals() );
    LUA_STATE.script( aCode, *mEnv );

    //TODO: DELETE (reflection test)
    sol::table metatable = (*mEnv);
    for (const auto &pair : metatable)
    {
      const std::string key = pair.first.as<std::string>();
      sol::type t = pair.second.get_type();
      LOG_INFO_APPLICATION( (key + " (" + std::to_string((int)t) + ")").c_str() );
    }
  }

  CScript::~CScript()
  {
    CHECKED_DELETE(mEnv);
  }

  void CScript::operator[](std::string aName)
  {
    auto f = (*mEnv)[aName];
    if (f.valid())
      f();
    else
      LOG_WARNING_APPLICATION("Function %s dont exist in Script.", aName);
  }

}