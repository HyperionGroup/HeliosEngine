#include "Editor.h"

#include "Logic\Script.h"

namespace editor
{
  template <> void GetAttributes<logic::CScript>(core::CAttributesTable& _attributes_table, const logic::CScript& _object)
  {
    auto v_lua_vars = _object.GetVarsVector();

    for each (auto var in v_lua_vars)
    {
      if (var.type == std::to_string((int)sol::type::number))
      {
        float val = var.value.as<float>();
        _attributes_table.AddAttribute(var.name.c_str(), val);
      }
      else
      {
        core::CStr val = var.value.as<core::CStr>();
        _attributes_table.AddAttribute(var.name.c_str(), val);
      }
    }
  }
}