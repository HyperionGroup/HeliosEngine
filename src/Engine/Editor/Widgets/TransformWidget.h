#pragma once

#include <QWidget>

#include "Core/Components.h"

namespace editor
{
  class CTransformWidget : public QWidget
  {
    Q_OBJECT
  public:
    CTransformWidget(core::TransformComponent* _transform);
    virtual ~CTransformWidget() = default;
  };
}