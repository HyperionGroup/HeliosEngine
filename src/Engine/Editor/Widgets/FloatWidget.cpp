#include "Editor.h"

#include "FloatWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>

namespace editor
{
  CFloatWidget::CFloatWidget(const char* _label, float* _float)
    : mSpinBox(new QDoubleSpinBox(this))
  {
    QHBoxLayout* lLayout = new QHBoxLayout(this);
    lLayout->addWidget(new QLabel( tr( _label ), this));
    lLayout->addWidget(mSpinBox);
    setLayout(lLayout);
  }
}