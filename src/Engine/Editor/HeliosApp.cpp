#include "Editor.h"
#include "HeliosApp.h"
#include "Widgets/MainWindow.h"
#include "Widgets/SceneView.h"

#include "Widgets/Docks/InspectorDock.h"

#include <QStyleFactory>
#include <QPalette>

#include <bgfx/bgfx.h>
#include "entry_p.h"
#include <bgfx_utils.h>

#include "imgui/imgui.h"

#include "Editor\HeliosApp.h"

namespace editor
{

  static CInspectorDock s_InspectorDock;

  CHeliosApp::~CHeliosApp()
  {
    CHECKED_DELETE(mMainWindow);
    CHECKED_DELETE(mMainWindow);
    CHECKED_DELETE(mQtApp);
  }

  void CHeliosApp::Run(int &argc, char **argv)
  {
    mFinish = false;
    HELIOSASSERT(!mQtApp);
    mQtApp = new QApplication(argc, argv);
    SetDllDirectoryA(".");
    QCoreApplication::addLibraryPath(".");
    mQtApp->setStyle(QStyleFactory::create("fusion"));
    mMainWindow = new CMainWindow();
    mSceneView = new CSceneView();

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(53, 53, 53));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, QColor(15, 15, 15));
    palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, QColor(53, 53, 53));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::BrightText, Qt::red);

    palette.setColor(QPalette::Highlight, QColor(142, 45, 197).lighter());
    palette.setColor(QPalette::HighlightedText, Qt::black);
    mQtApp->setPalette(palette);

    mMainWindow->AddDock( s_InspectorDock );

    s_InspectorDock.SetName("asdhfasdfasdfa");

    // Configure the main scene view
    entry::WindowHandle lSceneViewHandle = AddHandle((HWND)mSceneView->winId());
    mSceneView->SetWindowHandle(lSceneViewHandle);
    mMainWindow->setCentralWidget(mSceneView);

    mMainWindow->Show();

    MainThreadEntry mte;
    mte.m_argc = argc;
    mte.m_argv = argv;
    mte.m_App = this;

    thread.init(mte.threadFunc, &mte);
    mQtApp->exec();
    mFinish = true;
  }

  CInspectorDock& CHeliosApp::GetInspectorDock()
  {
    return s_InspectorDock;
  }

  int CHeliosApp::GetExitCode()
  {
    thread.shutdown();
    return thread.getExitCode();
  }

  const entry::Event* CHeliosApp::poll()
  {
    if(!mFinish)
      return mSceneView->poll();

    return new entry::Event(entry::Event::Exit);
  }

  void CHeliosApp::release(const entry::Event* _event) const
  {
    delete _event;
  }

  entry::WindowHandle CHeliosApp::FindHandle(HWND _hwnd)
  {
    bx::MutexScope scope(mLock);
    for (uint16_t ii = 0, num = mWindowAlloc.getNumHandles(); ii < num; ++ii)
    {
      uint16_t idx = mWindowAlloc.getHandleAt(ii);
      if (_hwnd == mHwnd[idx])
      {
        entry::WindowHandle handle = { idx };
        return handle;
      }
    }

    entry::WindowHandle invalid = { UINT16_MAX };
    return invalid;
  }

  entry::WindowHandle CHeliosApp::AddHandle(HWND _hwnd)
  {
    const uint16_t idx = mWindowAlloc.getNumHandles();
    bx::MutexScope scope(mLock);

    if (idx < ENTRY_CONFIG_MAX_WINDOWS)
    {
      mHwnd[idx] = _hwnd;
      mWindowAlloc.alloc();
      entry::WindowHandle handle = { idx };
      return handle;
    }

    entry::WindowHandle invalid = { UINT16_MAX };
    return invalid;
  }

  int32_t CHeliosApp::MainThreadEntry::threadFunc(void* _userData)
  {
    MainThreadEntry* self = (MainThreadEntry*)_userData;
    int32_t result = entry::main(self->m_argc, self->m_argv);
    return result;
  }
}