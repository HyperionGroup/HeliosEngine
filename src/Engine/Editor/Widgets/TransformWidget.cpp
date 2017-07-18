#include "Editor.h"
#include "TransformWidget.h"
#include "FloatWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

namespace editor
{
  CTransformWidget::CTransformWidget(core::TransformComponent * _transform)
  {
    QVBoxLayout* lLayout = new QVBoxLayout(this);

    QHBoxLayout* lPositionLayout = new QHBoxLayout(this);
    lPositionLayout->addWidget(new QLabel( tr("Position"), this));
    lPositionLayout->addWidget(new CFloatWidget("X", &(_transform->position.x)));
    lPositionLayout->addWidget(new CFloatWidget("Y", &(_transform->position.y)));
    lPositionLayout->addWidget(new CFloatWidget("Z", &(_transform->position.z)));
    lLayout->addLayout(lPositionLayout);

    QHBoxLayout* lRotationLayout = new QHBoxLayout(this);
    lRotationLayout->addWidget(new QLabel(tr("Rotation"), this));
    lRotationLayout->addWidget(new CFloatWidget("X", &(_transform->rotation.x)));
    lRotationLayout->addWidget(new CFloatWidget("Y", &(_transform->rotation.y)));
    lRotationLayout->addWidget(new CFloatWidget("Z", &(_transform->rotation.z)));
    lLayout->addLayout(lRotationLayout);

    QHBoxLayout* lScaleLayout = new QHBoxLayout(this);
    lScaleLayout->addWidget(new QLabel(tr("Scale"), this));
    lScaleLayout->addWidget(new CFloatWidget("X", &(_transform->scale.x)));
    lScaleLayout->addWidget(new CFloatWidget("Y", &(_transform->scale.y)));
    lScaleLayout->addWidget(new CFloatWidget("Z", &(_transform->scale.z)));
    lLayout->addLayout(lScaleLayout);

    lLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding));

    setLayout(lLayout);
  }
}