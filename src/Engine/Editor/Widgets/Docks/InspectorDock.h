#pragma once
#include <functional>

#include "Core/Core.h"

#include "Core/Utils/Singleton.h"
#include "Dock.h"

class QVBoxLayout;

namespace editor
{
  class CInspectorDock : public CDock, public core::CSingleton< CInspectorDock > 
  {
  public:
    CInspectorDock();
    virtual ~CInspectorDock() = default;
    template< typename T > void Inspect(T& _object)
    {
      core::CAttributesTable lTable;
      GetAttributes<T>(lTable, _object);
      Fill(lTable);
    }
    void Fill( const core::CAttributesTable& _table);
  };
}