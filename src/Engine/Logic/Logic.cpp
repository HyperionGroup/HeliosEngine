#include "Logic.h"

#include "Logger\Logger.h"

namespace logic
{
  void sol_example()
  {
    sol::state lua;
    // open some common libraries
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::jit);
    std::string sentence = lua.script("return 'bark bark bark!'");
    LOG_INFO_APPLICATION(sentence.c_str());
  }
}