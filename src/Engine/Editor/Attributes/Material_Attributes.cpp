#include "Editor.h"

#include "Gfx/Material.h"

namespace editor
{
  template <> void GetAttributes<gfx::CMaterial>(core::CAttributesTable& _attributes_table, const gfx::CMaterial& _object)
  {
  }
}