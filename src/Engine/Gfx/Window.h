#pragma once

namespace gfx
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
        
        bool HasFocus() const;
        Float2 GetWindowRelativeCursor() const;

        HWND winId() const { return hwnd; }

    protected:
        WNDCLASSEX wc;
        HWND hwnd;
        MSG msg;
        int mHeight;
        int mWidth;
        Float2  mPrevCursorPos;
    };
}