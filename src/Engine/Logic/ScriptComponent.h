#pragma once

#include <string>

#include <sol.hpp>

#include <anax/anax.hpp>
#include <anax/Entity.hpp>
#include <anax/Component.hpp>

namespace logic
{
  struct CScriptComponent : anax::Component
  {
    std::string mName;
    sol::function mStart;
    sol::function mUpdate;
  };
}