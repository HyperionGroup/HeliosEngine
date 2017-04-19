#pragma once

#ifndef _WINDOW_
#define _WINDOW_

#include <windows.h>

namespace user
{
    class CWindow
    {
    public:
        CWindow();
        virtual ~CWindow();
        virtual bool Create();
        virtual bool Update();
        virtual void ShutDown();

        HWND winID() const { return hwnd; }
    protected:
        WNDCLASSEX wc;
        HWND hwnd;
        MSG msg;

        virtual WNDPROC GetWNDPROC();
    };
}

#endif // !_WINDOW_