#pragma once

#include <QWidget>
class QDoubleSpinBox;

namespace editor
{
  class CFloatWidget : public QWidget
  {
  public:
    CFloatWidget( const char* _label, float* _float);
    virtual ~CFloatWidget() = default;
  private:
    QDoubleSpinBox* mSpinBox;
  };
}