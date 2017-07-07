#include "Logic.h"

#include "Script.h"

#include "Engine/Engine.h"

#include "ScriptManager.h"
#include "Str.h"

namespace logic
{

  CScript::CScript( std::string aCode, bool trace_variables )
  {
    mEnv = new sol::environment(LUA_STATE, sol::create, LUA_STATE.globals() );
    LUA_STATE.script( aCode, *mEnv );

    if (trace_variables)
    {
      sol::table env_table = (*mEnv);
      for (const auto &pair : env_table)
      {
        SLuaVar var;
        var.name = pair.first.as<std::string>();
        sol::type type = pair.second.get_type();
        var.value = pair.second.as<sol::object>();

        if (type == sol::type::userdata)
        {
          LUA_STATE.script("actual_check_usertype = " + var.name + ":cpp_type()", *mEnv);
          std::string type = (*mEnv)["actual_check_usertype"];
          var.type = type;
        }
        else
        {
          var.type = std::to_string((int)type);
        }

        mVariables.push_back(var);
      }
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
      LOG_WARNING_APPLICATION("Function %s dont exist in Script.", aName.c_str());
  }

}