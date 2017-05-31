#include "Engine.h"

#pragma once

#include "Window.h"
#include "Engine.h"
#include "d3d11\Device.h"
#include "imgui.h"

namespace
{
    static LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _umsg, WPARAM _wparam, LPARAM _lparam)
    {
        ImGuiIO& imgui = ImGui::GetIO();
        helios::CWindow lWindow = helios::CEngine::GetInstance().GetWindow();
        switch (_umsg) {
        case WM_SIZE: {
            int w = (int)LOWORD(_lparam), h = (int)HIWORD(_lparam);
            if (lWindow.GetWidth() != w || lWindow.GetHeight() != h)
            {
                lWindow.SetWidth(w);
                lWindow.SetHeight(h);
            }
#if defined(HELIOSDX11)
            // DX requires that we reset the backbuffer when the window resizes
            if (g_Example->m_d3dRenderTarget) {
                g_Example->m_d3dRenderTarget->Release();
                g_Example->m_d3dDepthStencil->Release();
                dxAssert(g_Example->m_dxgiSwapChain->ResizeBuffers(0, (UINT)w, (UINT)h, DXGI_FORMAT_UNKNOWN, 0));
                ID3D11Texture2D* backBuffer;
                dxAssert(g_Example->m_dxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer));
                dxAssert(g_Example->m_d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &g_Example->m_d3dRenderTarget));
                g_Example->m_d3dDepthStencil = CreateDepthStencil((UINT)w, (UINT)h, DXGI_FORMAT_D24_UNORM_S8_UINT);
                g_Example->m_d3dDeviceCtx->OMSetRenderTargets(1, &g_Example->m_d3dRenderTarget, g_Example->m_d3dDepthStencil);
                backBuffer->Release();
            }

#endif
            break;
        }
        case WM_SIZING: {
            RECT* r = (RECT*)_lparam;
            int w = (int)(r->right - r->left);
            int h = (int)(r->bottom - r->top);
            if (lWindow.GetWidth() != w || lWindow.GetHeight() != h)
            {
                lWindow.SetWidth(w);
                lWindow.SetHeight(h);
            }
            break;
        }
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
            imgui.MouseDown[0] = _umsg == WM_LBUTTONDOWN;
            break;
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
            imgui.MouseDown[2] = _umsg == WM_MBUTTONDOWN;
            break;
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            imgui.MouseDown[1] = _umsg == WM_RBUTTONDOWN;
            break;
        case WM_MOUSEWHEEL:
            imgui.MouseWheel = (float)(GET_WHEEL_DELTA_WPARAM(_wparam)) / (float)(WHEEL_DELTA);
            break;
        case WM_MOUSEMOVE:
            imgui.MousePos.x = LOWORD(_lparam);
            imgui.MousePos.y = HIWORD(_lparam);
            break;
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYDOWN:
        case WM_KEYUP: {
            WPARAM vk = _wparam;
            UINT sc = (_lparam & 0x00ff0000) >> 16;
            bool e0 = (_lparam & 0x01000000) != 0;
            if (vk == VK_SHIFT) {
                vk = MapVirtualKey(sc, MAPVK_VSC_TO_VK_EX);
            }
            switch (vk) {
            case VK_CONTROL:
                imgui.KeyCtrl = _umsg == WM_KEYDOWN;
                break;
            case VK_MENU:
                imgui.KeyAlt = _umsg == WM_KEYDOWN;
                break;
            case VK_LSHIFT:
            case VK_RSHIFT:
                imgui.KeyShift = _umsg == WM_KEYDOWN;
                break;
            case VK_ESCAPE:
                PostQuitMessage(0);
                break;
            default:
                if (vk < 512) {
                    imgui.KeysDown[vk] = _umsg == WM_KEYDOWN;
                }
                break;
            };
            return 0;
        }
        case WM_CHAR:
            if (_wparam > 0 && _wparam < 0x10000) {
                imgui.AddInputCharacter((unsigned short)_wparam);
            }
            return 0;
        case WM_PAINT:
            //HELIOSASSERT(false); // should be suppressed by calling ValidateRect()
            break;
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0; // prevent DefWindowProc from destroying the window
        default:
            break;
        };
        return DefWindowProc(_hwnd, _umsg, _wparam, _lparam);
    }
}

namespace helios
{
    CWindow::CWindow()
    {
        ZeroMemory(&msg, sizeof(msg));
    }

    CWindow::~CWindow()
    {
        ShutDown();
    }

    bool CWindow::Create(int _height, int _width) 
    {
        SetWidth(_width);
        SetHeight(_height);
        static ATOM wndclassex = 0;
        if (wndclassex == 0)
        {
            WNDCLASSEX wc;
            memset(&wc, 0, sizeof(wc));
            wc.cbSize = sizeof(wc);
            wc.style = CS_OWNDC;// | CS_HREDRAW | CS_VREDRAW;
            wc.lpfnWndProc = WindowProc;
            wc.hInstance = GetModuleHandle(0);
            wc.lpszClassName = "HeliosApp";
            wc.hCursor = LoadCursor(0, IDC_ARROW);
            winAssert(wndclassex = RegisterClassEx(&wc));
        }
        DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_MINIMIZEBOX | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

        if (GetWidth() == -1 || GetHeight() == -1)
        {
            // auto size; get the dimensions of the primary screen area and subtract the non-client area
            RECT r;
            winAssert(SystemParametersInfo(SPI_GETWORKAREA, 0, &r, 0));
            SetWidth(r.right - r.left);
            SetHeight(r.bottom - r.top);

            RECT wr = {};
            winAssert(AdjustWindowRectEx(&wr, dwStyle, FALSE, dwExStyle));
            SetWidth(GetWidth() - wr.right - wr.left);
            SetHeight(GetHeight() - wr.bottom - wr.top);
        }

        RECT r; r.top = 0; r.left = 0; r.bottom = GetHeight(); r.right = GetWidth();
        winAssert(AdjustWindowRectEx(&r, dwStyle, FALSE, dwExStyle));
        hwnd = CreateWindowEx(
            dwExStyle,
            MAKEINTATOM(wndclassex),
            "HeliosApp",
            dwStyle,
            0, 0,
            r.right - r.left, r.bottom - r.top,
            nullptr,
            nullptr,
            GetModuleHandle(0),
            nullptr
        );
        HELIOSASSERT_MSG(hwnd, "Null handle for window");
        ShowWindow(hwnd, SW_SHOW);
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
        UnregisterClass(("HeliosApp"), wc.hInstance);
    }

    WNDPROC CWindow::GetWNDPROC()
    {
        return WindowProc;
    }

    bool CWindow::HasFocus() const { return hwnd == GetFocus(); }

    Float2 CWindow::GetWindowRelativeCursor() const
    {
        #if defined(HELIOSPLATFORM_WIN)
                POINT p = {};
                winAssert(GetCursorPos(&p));
                winAssert(ScreenToClient(hwnd, &p));
                return Float2((float)p.x, (float)p.y);
        #endif
    }

}