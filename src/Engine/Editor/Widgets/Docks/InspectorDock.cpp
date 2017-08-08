#include "Editor.h"
#include "InspectorDock.h"

#include "Widgets/Widget.h"

#include <QDockWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <qtimer.h>

#include "Widgets/WidgetFactory.h"

namespace editor
{
  QDockWidget* CInspectorDock::CreateDock()
  {
    mDock = new QDockWidget("Inspector");
    mDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QTimer *timer = new QTimer(mDock);
    QObject::connect(timer, &QTimer::timeout, [this]() { Fill(lTable); });
    timer->start(0);

    mUpdate = false;

    return mDock;
  }

  void CInspectorDock::Fill( const core::CAttributesTable & _table)
  {
    if (mUpdate)
    {
      CWidgetFactory& lWidgetFactory = CWidgetFactory::GetInstance();
      QScrollArea* lScrollArea = new QScrollArea();
      QVBoxLayout* lMainLayout = new QVBoxLayout(lScrollArea);
      for (size_t i = 0, lCount = _table.Length(); i < lCount; ++i)
        lMainLayout->addWidget(lWidgetFactory.Create(_table.GetByIdx(i)));
      lMainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding));
      lScrollArea->setLayout(lMainLayout);
      mDock->setWidget(lScrollArea);
      mUpdate = false;
    }
  }
}
