#include "Editor.h"
#include "InspectorDock.h"

#include "Widgets/Widget.h"

#include <QDockWidget>
#include <QVBoxLayout>
#include <QScrollArea>

#include "Widgets/WidgetFactory.h"

namespace editor
{
  CInspectorDock::CInspectorDock()
    : CDock()
  {
    mDock = new QDockWidget("Inspector");
    mDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
  }

  void CInspectorDock::Fill( const core::CAttributesTable & _table)
  {
    CWidgetFactory& lWidgetFactory = CWidgetFactory::GetInstance();
    QScrollArea* lScrollArea = new QScrollArea();
    QVBoxLayout* lMainLayout = new QVBoxLayout(lScrollArea);
    for (size_t i = 0, lCount = _table.Length(); i < lCount; ++i)
      lMainLayout->addWidget(lWidgetFactory.Create(_table.GetByIdx(i)));
    lMainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding));
    lScrollArea->setLayout(lMainLayout);
    mDock->setWidget(lScrollArea);
  }
}
