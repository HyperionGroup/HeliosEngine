#pragma once
#include <QMainWindow>

#include "Widgets/Docks/Dock.h"

namespace editor
{
  class CMainWindow : public QMainWindow
  {
  public:
    CMainWindow() = default;
    virtual ~CMainWindow() = default;
    void AddDock(const CDock& _dock) { addDockWidget(Qt::LeftDockWidgetArea, _dock.GetDock()); }
    void Show() { showMaximized(); }
  };
}