#include "Gfx.h"
#include "Window.h"

namespace render
{
    CWindow::CWindow()
    {
    }

    CWindow::~CWindow()
    {
    }

    bool CWindow::Create(int _height, int _width) 
    {
        return false;
    }

    bool CWindow::Update()
    {
        return false;
    }

    void CWindow::ShutDown()
    {
    }

    bool CWindow::HasFocus() const { return hwnd == GetFocus(); }

    Float2 CWindow::GetWindowRelativeCursor() const
    {
        return Float2();
    }

}