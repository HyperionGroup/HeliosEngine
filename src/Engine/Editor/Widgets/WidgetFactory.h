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
  };
}