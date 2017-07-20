#pragma once

#include "Core/Core.h"

#include <QWidget>

class QDoubleSpinBox;
class QLineEdit;

namespace editor
{
  template < typename T, typename Q >
  class CWidget : public QWidget
  {
  public:
    CWidget(const char* _label, T* _value, bool _enabled = true);
    virtual ~CWidget() = default;
    virtual void SetCSS(const char * style);
  protected:
    Q* mEditableWidget;
    T* mValue;
  };

  class CFloatWidget : public CWidget<float, QDoubleSpinBox>
  {
  public:
    CFloatWidget(const char* _label, float* _value, bool _enabled = true);
    virtual ~CFloatWidget() = default;
  };

  class CStrWidget : public CWidget<core::CStr, QLineEdit>
  {
  public:
    CStrWidget(const char* _label, core::CStr* _value, bool _enabled = true);
    virtual ~CStrWidget() = default;
  };
  
}