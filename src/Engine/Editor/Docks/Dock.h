#pragma once
#include "Core/Core.h"
#include "Core/AttributesTable.h"
#include "Core/Name.h"

class QDockWidget;

namespace editor
{
  class CDock : public core::CName
  {
  public:
    CDock() = default;
    virtual ~CDock() = default;
    QDockWidget* GetDock() const { return mDock; }
  protected:
    QDockWidget* mDock;
  };
}