#pragma once

#include <QWidget>

#include "Core/Entities/Components.h"

namespace editor
{
  class CTransformWidget : public QWidget
  {
    Q_OBJECT
  public:
    CTransformWidget(const char* _label, core::TransformComponent* _transform, bool _editable);
    virtual ~CTransformWidget() = default;
  };
}