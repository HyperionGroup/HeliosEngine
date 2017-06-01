#include "Logic.h"

namespace logic
{
  void sol_example()
  {
    sol::state lua;
    // open some common libraries
    lua.open_libraries(sol::lib::base, sol::lib::package);
    lua.script("print('bark bark bark!')");
  }
}