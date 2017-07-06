#pragma once

#include <string>
#include <vector>

#include <sol.hpp>

namespace logic
{
  struct SLuaVar
  {
    std::string name;
    sol::type type;
    std::string value;
  };

  class CScript
  {
  public:
    CScript(std::string aCode);
    ~CScript();

    void operator [](std::string aName);

  private:
    sol::environment *mEnv;

    std::vector<SLuaVar> mVariables;
  };
}