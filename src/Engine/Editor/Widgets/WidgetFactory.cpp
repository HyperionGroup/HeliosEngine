#include "Editor.h"

#include "Core/Entities/Components.h"

#include "WidgetFactory.h"
#include "Widget.h"
#include "TransformWidget.h"

namespace editor
{
  CWidgetFactory::CWidgetFactory()
  {
    NEW_WIDGET<float, CFloatWidget>();
    NEW_WIDGET<core::CStr, CStrWidget>();
    NEW_WIDGET<core::TransformComponent, CTransformWidget>();
  }
}