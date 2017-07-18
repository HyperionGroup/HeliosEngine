#include "Editor.h"

#include "FloatWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>

namespace editor
{
  CFloatWidget::CFloatWidget(const char* _label, float* _float)
    : mSpinBox(new QDoubleSpinBox(this))
    , mValue(_float)
  {
    mSpinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    QHBoxLayout* lLayout = new QHBoxLayout(this);
    lLayout->setMargin(0);
    if(_label && std::strcmp(_label, "") != 0)
      lLayout->addWidget(new QLabel(tr(_label), this));
    lLayout->addWidget(mSpinBox);
    mSpinBox->setValue(*_float);
    mSpinBox->setMinimumSize(40, 20);
    QObject::connect(mSpinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [this](const double d) { *mValue = d; });
    setLayout(lLayout);
  }

  void CFloatWidget::SetStylesheet(const char* _style)
  {
      mSpinBox->setStyleSheet(_style);
  }
}