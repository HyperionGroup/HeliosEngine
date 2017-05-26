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
        virtual bool Create( int _height = -1, int _width = -1);
        virtual bool Update();
        virtual void ShutDown();

        HWND winID() const { return hwnd; }
        int GetHeight() const { return mHeight; }
        void SetHeight(int val) { mHeight = val; }
        int GetWidth() const { return mWidth; }
        void SetWidth(int val) { mWidth = val; }
    protected:
        WNDCLASSEX wc;
        HWND hwnd;
        MSG msg;
        int mHeight;
        int mWidth;

        virtual WNDPROC GetWNDPROC();
    };
}

#endif // !_WINDOW_