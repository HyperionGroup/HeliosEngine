#include "Editor.h"
#include "TransformWidget.h"
#include "FloatWidget.h"

#include <QGridLayout>
#include <QLabel>

namespace
{
  void AddTransformWidget(QGridLayout* _layout, const char* _label, float*_x, float*_y, float*_z, int _row)
  {
    _layout->addWidget(new QLabel(QObject::tr(_label)), _row, 0, Qt::AlignLeft);
    editor::CFloatWidget* lX = new editor::CFloatWidget("X", _x );
    lX->SetStylesheet("QDoubleSpinBox { background-color: #990000; }");
    editor::CFloatWidget* lY = new editor::CFloatWidget("Y", _z);
    lY->SetStylesheet("QDoubleSpinBox { background-color: #009900; }");
    editor::CFloatWidget* lZ = new editor::CFloatWidget("Z", _y );
    lZ->SetStylesheet("QDoubleSpinBox { background-color: #000099; }");
    _layout->addWidget(lX, _row, 1, Qt::AlignLeft);
    _layout->addWidget(lY, _row, 2, Qt::AlignLeft);
    _layout->addWidget(lZ, _row, 3, Qt::AlignLeft);
  }
}

namespace editor
{
  CTransformWidget::CTransformWidget(core::TransformComponent * _transform)
  {
    QGridLayout* lLayout = new QGridLayout(this);
    lLayout->setMargin(0);
    AddTransformWidget(lLayout, "Position", &(_transform->position.x), &(_transform->position.y), &(_transform->position.z), 0);
    AddTransformWidget(lLayout, "Rotation", &(_transform->rotation.x), &(_transform->rotation.y), &(_transform->rotation.z), 1);
    AddTransformWidget(lLayout, "Scale", &(_transform->scale.x), &(_transform->scale.y), &(_transform->scale.z), 2);
    lLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum),0,3);
    setLayout(lLayout);
  }
}