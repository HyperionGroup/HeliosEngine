#include "Editor.h"

#include "Core/Entities/Components.h"

namespace editor
{
  template <> void GetAttributes<core::TransformComponent>(core::CAttributesTable& _attributes_table, const core::TransformComponent& _object)
  {
    _attributes_table.AddAttribute("Transform", _object);
  }
}