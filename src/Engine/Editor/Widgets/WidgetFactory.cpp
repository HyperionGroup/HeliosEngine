#include "Editor.h"

#include "Core/Entities/Components.h"

#include "WidgetFactory.h"
#include "Widget.h"
#include "TransformWidget.h"

namespace editor
{
#define NEW_WIDGET( type, widget_class_name )\
mCreators[typeid(type).hash_code()] = [](std::shared_ptr<core::CAttribute> _att)\
{ return new widget_class_name(_att->GetName().c_str(), _att->As<type>(), _att->IsEditable()); }

  CWidgetFactory::CWidgetFactory()
  {
    NEW_WIDGET(float, CFloatWidget);
    NEW_WIDGET(core::CStr, CStrWidget);
    NEW_WIDGET(core::TransformComponent, CTransformWidget);
  }
}