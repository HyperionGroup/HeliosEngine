#pragma once

#include <string>

#include <sol.hpp>

namespace logic
{
  class CScript
  {
    CScript(std::string aCode);
    ~CScript();

    void operator [](std::string aName);

  private:
    sol::environment mEnv;
  };
}