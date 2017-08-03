#pragma once
#include "Core/Core.h"

#include "entry_p.h"

#include <QWidget>

namespace editor
{
  class CSceneView : public QWidget, public entry::EventQueue
  {
  public:
    CSceneView();
    virtual ~CSceneView() = default;
    void SetWindowHandle(const entry::WindowHandle& _handle) { mHandle = _handle; }
  protected:
    virtual void resizeEvent(QResizeEvent * event);
    virtual void	mouseMoveEvent(QMouseEvent * event);
    virtual void	mousePressEvent(QMouseEvent * event);
    virtual void	mouseReleaseEvent(QMouseEvent * event);

    entry::WindowHandle mHandle;
    bool mRightButtonPressed;
    bool mLeftButtonPressed;
    bool mMiddleButtonPressed;
  };
}