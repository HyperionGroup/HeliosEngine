#include "Editor.h"
#include "Widget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QLineEdit>

namespace editor
{
  template<typename T, typename Q>
  CWidget<T, Q>::CWidget(const char * _label, T* _value, bool _enabled)
    : mValue(_value)
  {
    // Create the widget needed to display the kind of data of the type
    mEditableWidget = new Q();
    mEditableWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    mEditableWidget->setMinimumSize(40, 20);

    // Create a horizontal layout with the label and the widget
    QHBoxLayout* lLayout = new QHBoxLayout(this);
    lLayout->setMargin(0);

    // Check the label, if it is null do not put the label widget
    if (_label && std::strcmp(_label, "") != 0)
      lLayout->addWidget(new QLabel(tr(_label), this));
    lLayout->addWidget(mEditableWidget);

    // Set to this object the whole widget 
    setLayout(lLayout);

    // Enable the whole widget in case that it is editable
    setEnabled(_enabled);
  }

  template<typename T, typename Q>
  void CWidget<T, Q>::SetCSS(const char * style)
  {
    mEditableWidget->setStyleSheet(style);
  }

  CFloatWidget::CFloatWidget(const char* _label, float* _value, bool _enabled)
    : CWidget(_label, _value, _enabled)
  {
    mEditableWidget->setValue(*_value);
    QObject::connect(mEditableWidget, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [this](const double d) { *mValue = d; });
  }

  CStrWidget::CStrWidget(const char * _label, core::CStr * _value, bool _enabled)
    : CWidget(_label, _value, _enabled)
  {
    mEditableWidget->setText( _value->c_str() );
  }
}