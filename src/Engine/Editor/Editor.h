#pragma once
#include "Core/Core.h"

#include "Core/AttributesTable.h"
#include "Core/Utils/Singleton.h"
#include "Core/Name.h"

namespace editor
{
  template < typename T > void GetHierarchy(core::CAttributesTable& _attributes_table, const T& _object);
  template < typename T > void GetAttributes(core::CAttributesTable& _attributes_table, const T& _object);
}