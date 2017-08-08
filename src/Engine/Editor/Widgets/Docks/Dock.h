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
    QDockWidget* GetDock() { if (!mDock) { mDock = CreateDock(); } return mDock; }

  protected:
    virtual QDockWidget* CreateDock() = 0;
    QDockWidget* mDock;
  };
}