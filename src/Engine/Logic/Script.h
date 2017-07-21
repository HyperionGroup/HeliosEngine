#pragma once

#include <string>
#include <vector>

#include <sol.hpp>

namespace logic
{
  struct SLuaVar
  {
    std::string name;
    std::string type;
    sol::object value;
  };

  class CScript
  {
  public:
    CScript(std::string aCode, bool trace_variables = true);
    ~CScript();

    void operator [](std::string aName);

    std::vector<SLuaVar> GetVarsVector() const { return mVariables; }

  private:
    sol::environment *mEnv;

    std::vector<SLuaVar> mVariables;
  };
}