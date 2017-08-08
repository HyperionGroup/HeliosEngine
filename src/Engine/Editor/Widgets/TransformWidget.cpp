#include "Editor.h"
#include "TransformWidget.h"
#include "Widget.h"
#include <QGridLayout>
#include <QLabel>

namespace
{
  void AddTransformWidget(QGridLayout* _layout, const char* _label, float*_x, float*_y, float*_z, int _row)
  {
    _layout->addWidget(new QLabel(QObject::tr(_label)), _row, 0);
    editor::CFloatWidget* lX = new editor::CFloatWidget("X", _x );
    lX->SetCSS("QDoubleSpinBox { background-color: #990000; }");
    editor::CFloatWidget* lY = new editor::CFloatWidget("Y", _y);
    lY->SetCSS("QDoubleSpinBox { background-color: #009900; }");
    editor::CFloatWidget* lZ = new editor::CFloatWidget("Z", _z );
    lZ->SetCSS("QDoubleSpinBox { background-color: #000099; }");
    _layout->addWidget(lX, _row, 1);
    _layout->addWidget(lY, _row, 2);
    _layout->addWidget(lZ, _row, 3);
  }
}

namespace editor
{
  CTransformWidget::CTransformWidget(const char*, core::TransformComponent * _transform, bool _editable)
  {
    QGridLayout* lLayout = new QGridLayout(this);
    lLayout->setMargin(0);
    AddTransformWidget(lLayout, "Position", &(_transform->position.x), &(_transform->position.y), &(_transform->position.z), 0);
    AddTransformWidget(lLayout, "Rotation", &(_transform->rotation.x), &(_transform->rotation.y), &(_transform->rotation.z), 1);
    AddTransformWidget(lLayout, "Scale", &(_transform->scale.x), &(_transform->scale.y), &(_transform->scale.z), 2);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    setLayout(lLayout);
  }
}