#include "Editor.h"

#include "HeliosApp.h"

#if BX_PLATFORM_WINDOWS

static editor::CHeliosApp s_App;

namespace entry
{
  void setMousePos(HWND , int32_t , int32_t )
  {

  }

  void setMouseLock(HWND , bool )
  {
    
  }

  void setWindowPos(WindowHandle , int32_t , int32_t )
  {
   
  }

  void setWindowSize(WindowHandle , uint32_t , uint32_t )
  {
    
  }

  void setWindowTitle(WindowHandle , const char* )
  {
   
  }

  void toggleWindowFrame(WindowHandle )
  {
    
  }

  void toggleFullscreen(WindowHandle )
  {
    
  }

  void setMouseLock(WindowHandle , bool )
  {

  }

  const Event* poll(WindowHandle )
  { 
    return nullptr;
  }

  const Event* poll()
  {
    return s_App.poll();
  }

  void release(const Event* _event)
  {
    s_App.release(_event);
  }
}

int main(int _argc, char** _argv)
{
  s_App.Run(_argc, _argv);
  return s_App.GetExitCode();
}

#endif