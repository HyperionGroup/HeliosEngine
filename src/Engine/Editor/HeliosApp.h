#pragma once

#include <QApplication>
#include <bx/handlealloc.h>
#include <bx/mutex.h>

#include "entry_p.h"
#include <bx/thread.h>

namespace editor
{
  class CMainWindow;
  class CSceneView;
  class CInspectorDock;
  class CHeliosApp
  {
  public:
    CHeliosApp() = default;
    virtual ~CHeliosApp();

    void Run(int &argc, char **argv);
    int GetExitCode();

    const entry::Event* poll();
    void release(const entry::Event* _event) const;

    CMainWindow* GetMainWindow() const { return mMainWindow; }
    CSceneView* GetSceneView() const { return mSceneView; }

    static CInspectorDock& GetInspectorDock();

  private:
    HWND mHwnd[8];
    bx::HandleAllocT<8> mWindowAlloc;
    bx::Mutex mLock;
    bx::Thread thread;

    struct MainThreadEntry
    {
      int m_argc;
      const char* const* m_argv;
      CHeliosApp* m_App;

      static int32_t threadFunc(void* _userData);
    };

    CMainWindow* mMainWindow;
    CSceneView*  mSceneView;

    entry::WindowHandle FindHandle(HWND _hwnd);
    entry::WindowHandle AddHandle(HWND _hwnd);
    QApplication* mQtApp;
    
    bool mFinish;
  };
}