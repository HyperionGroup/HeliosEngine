#include "Editor.h"

#include "SceneView.h"

#include <bgfx/platform.h>
#include <bx/os.h>

#include <QResizeEvent>
#include <QMouseEvent>

namespace editor
{
  CSceneView::CSceneView()
  {
    bgfx::PlatformData pd;
    bx::memSet(&pd, 0, sizeof(pd));
    pd.nwh = (HWND)winId();
    bgfx::setPlatformData(pd);
    setMouseTracking(true);
  }

  void CSceneView::resizeEvent(QResizeEvent * event)
  {
    postSizeEvent(mHandle, event->size().width(), event->size().height() );
  }

  void	CSceneView::mouseMoveEvent(QMouseEvent * event)
  {
    switch (event->button())
    {
    case Qt::LeftButton:
      postMouseEvent(mHandle, event->pos().x(), event->pos().y(), 0, entry::MouseButton::Left, true);
      LOG_INFO_APPLICATION("LeftButton %d %d", event->pos().x(), event->pos().y());
      break;
    case Qt::MiddleButton:
      postMouseEvent(mHandle, event->pos().x(), event->pos().y(), 0, entry::MouseButton::Middle, true);
      LOG_INFO_APPLICATION("MiddleButton %d %d", event->pos().x(), event->pos().y());
      break;
    case Qt::RightButton:
      LOG_INFO_APPLICATION("RightButton %d %d", event->pos().x(), event->pos().y());
      postMouseEvent(mHandle, event->pos().x(), event->pos().y(), 0, entry::MouseButton::Right, true);
      break;
    default:
      LOG_INFO_APPLICATION("default %d %d", event->pos().x(), event->pos().y());
      postMouseEvent(mHandle, event->pos().x(), event->pos().y(), 0);
    }
  }

  void	CSceneView::mousePressEvent(QMouseEvent * event)
  {
    switch (event->button())
    {
    case Qt::LeftButton:
      mLeftButtonPressed = true;
      postMouseEvent(mHandle, event->pos().x(), event->pos().y(), 0, entry::MouseButton::Left, true);
      LOG_INFO_APPLICATION("LeftButton pressed %d %d", event->pos().x(), event->pos().y());
      break;
    case Qt::MiddleButton:
      mMiddleButtonPressed = true;
      postMouseEvent(mHandle, event->pos().x(), event->pos().y(), 0, entry::MouseButton::Middle, true);
      LOG_INFO_APPLICATION("MiddleButton pressed %d %d", event->pos().x(), event->pos().y());
      break;
    case Qt::RightButton:
      mRightButtonPressed = true;
      LOG_INFO_APPLICATION("RightButton pressed %d %d", event->pos().x(), event->pos().y());
      postMouseEvent(mHandle, event->pos().x(), event->pos().y(), 0, entry::MouseButton::Right, true);
      break;
    default:
      LOG_INFO_APPLICATION("default pressed %d %d", event->pos().x(), event->pos().y());
      postMouseEvent(mHandle, event->pos().x(), event->pos().y(), 0);
    }
  }

  void	CSceneView::mouseReleaseEvent(QMouseEvent * event)
  {
    switch (event->button())
    {
    case Qt::LeftButton:
      postMouseEvent(mHandle, event->pos().x(), event->pos().y(), 0, entry::MouseButton::Left, false);
      mLeftButtonPressed = false;
      LOG_INFO_APPLICATION("LeftButton released %d %d", event->pos().x(), event->pos().y());
      break;
    case Qt::MiddleButton:
      postMouseEvent(mHandle, event->pos().x(), event->pos().y(), 0, entry::MouseButton::Middle, false);
      mMiddleButtonPressed = false;
      LOG_INFO_APPLICATION("MiddleButton released %d %d", event->pos().x(), event->pos().y());
      break;
    case Qt::RightButton:
      LOG_INFO_APPLICATION("RightButton released %d %d", event->pos().x(), event->pos().y());
      mRightButtonPressed = false;
      postMouseEvent(mHandle, event->pos().x(), event->pos().y(), 0, entry::MouseButton::Right, false);
      break;
    default:
      LOG_INFO_APPLICATION("default released %d %d", event->pos().x(), event->pos().y());
      postMouseEvent(mHandle, event->pos().x(), event->pos().y(), 0);
    }
  }
}