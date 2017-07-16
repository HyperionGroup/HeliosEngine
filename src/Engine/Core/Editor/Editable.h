#pragma once

#include "Core/Str.h"
#include "Core/Logger/Logger.h"

namespace editor
{
  class CEditable
  {
  public:
    CEditable() = default;
    virtual ~CEditable() = default;
    virtual void OnEditor() = 0;
  };
}