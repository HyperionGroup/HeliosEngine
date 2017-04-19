#pragma once

#include "Window.h"
#include "d3d11\Device.h"

namespace
{
    LRESULT WINAPI WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        case WM_SIZE:
        {
            render::CDevice lDevice = render::CDevice::GetInstance();
            lDevice.SetBackBufferWidth((UINT)LOWORD(lParam));
            lDevice.SetBackBufferHeight((UINT)HIWORD(lParam));
            lDevice.Reset();
            return 0;
        }
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

namespace user
{

    CWindow::CWindow()
    {
        ZeroMemory(&msg, sizeof(msg));
    }

    CWindow::~CWindow()
    {
        ShutDown();
    }

    bool CWindow::Create()
    {
        WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, GetWNDPROC(), 0L, 0L, GetModuleHandle(NULL), NULL, LoadCursor(NULL, IDC_ARROW), NULL, NULL, ("HeliosEditor"), NULL };
        RegisterClassEx(&wc);
        hwnd = CreateWindow(("HeliosEditor"), ("HeliosEditor"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);
        if (hwnd)
        {
            render::CDevice::GetInstance().Initialize(hwnd);
            ShowWindow(hwnd, SW_SHOWDEFAULT);
        }
        return hwnd != nullptr;
    }

    bool CWindow::Update()
    {
        while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                return false;
        }

        UpdateWindow(hwnd);
        return true;
    }

    void CWindow::ShutDown()
    {
        UnregisterClass(("HeliosEditor"), wc.hInstance);
    }

    WNDPROC CWindow::GetWNDPROC()
    {
        return WndProcHandler;
    }

}