#pragma once

#include "Core/Core.h"
#include <functional>

class QWidget;

namespace editor
{
  class CWidgetFactory : public core::CSingleton<CWidgetFactory>
  {
  public:
    CWidgetFactory();
    ~CWidgetFactory() = default;
    QWidget* Create(std::shared_ptr<core::CAttribute> _att)
    {
      HELIOSASSERT(mCreators.find(_att->Hash()) != mCreators.end());
      return mCreators[_att->Hash()](_att);
    }
  private:
    std::map < const size_t , std::function<QWidget*(std::shared_ptr<core::CAttribute>)>> mCreators;

    template < typename type, typename widget >
    void NEW_WIDGET()
    {
      mCreators[typeid(type).hash_code()] = [](std::shared_ptr<core::CAttribute> _att)
      {
        return new widget(_att->GetName().c_str(), _att->As<type>(), _att->IsEditable());
      };
    }
  };
}