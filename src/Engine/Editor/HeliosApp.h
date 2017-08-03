#pragma once

#include <QApplication>
#include <bx/handlealloc.h>
#include <bx/mutex.h>

#include "entry_p.h"

namespace editor
{
  class CMainWindow;
  class CSceneView;
  class CHeliosApp
  {
  public:
    CHeliosApp() = default;
    virtual ~CHeliosApp();

    void Init(int &argc, char **argv);
    void Run();

    const entry::Event* poll();
    bool ProcessEvents(uint32_t& _width, uint32_t& _height);
    CMainWindow* GetMainWindow() const { return mMainWindow; }
    CSceneView* GetSceneView() const { return mSceneView; }

  private:
    HWND mHwnd[8];
    bx::HandleAllocT<8> mWindowAlloc;
    bx::Mutex mLock;

    CMainWindow* mMainWindow;
    CSceneView*  mSceneView;

    entry::WindowHandle FindHandle(HWND _hwnd);
    entry::WindowHandle AddHandle(HWND _hwnd);
    QApplication* mQtApp;
    bool mFinish;
  };
}