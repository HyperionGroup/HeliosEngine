#pragma once
#include <functional>

#include "Core/Core.h"
#include "Editor/Editor.h"
#include "AttributesTable.h"

#include "Core/Utils/Singleton.h"
#include "Dock.h"

class QVBoxLayout;

namespace editor
{
  class CInspectorDock : public CDock
  {
  public:
    CInspectorDock() = default;
    virtual ~CInspectorDock() = default;
    virtual QDockWidget* CreateDock();
    template< typename T > void Inspect(T& _object)
    {
      lTable.Clear();
      GetAttributes<T>(lTable, _object);
      mUpdate = true;
    }
    void Fill( const core::CAttributesTable& _table);

  private:
    bool mUpdate;
    core::CAttributesTable lTable;
  };
}