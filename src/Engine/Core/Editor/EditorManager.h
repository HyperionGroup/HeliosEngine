#pragma once

#include "Core/Singleton.h"

namespace editor
{
  class CEditable;
  class CEditorManager : public core::CSingleton< CEditorManager >
  {
  public:
    CEditorManager() = default;
    virtual ~CEditorManager() = default;
    void Update();
  public:
    std::shared_ptr< CEditable > mCurrentObject;
  };
}