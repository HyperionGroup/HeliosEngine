#include "Render.h"

#include "Window.h"
#include "Engine.h"
#include "d3d11\Device.h"
#include "imgui.h"

namespace
{
    static LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _umsg, WPARAM _wparam, LPARAM _lparam)
    {
        ImGuiIO& imgui = ImGui::GetIO();
        switch (_umsg)
        {
        case WM_LBUTTONDOWN:
            imgui.MouseDown[0] = true;
            return true;
        case WM_LBUTTONUP:
            imgui.MouseDown[0] = false;
            return true;
        case WM_RBUTTONDOWN:
            imgui.MouseDown[1] = true;
            return true;
        case WM_RBUTTONUP:
            imgui.MouseDown[1] = false;
            return true;
        case WM_MBUTTONDOWN:
            imgui.MouseDown[2] = true;
            return true;
        case WM_MBUTTONUP:
            imgui.MouseDown[2] = false;
            return true;
        case WM_MOUSEWHEEL:
            imgui.MouseWheel += GET_WHEEL_DELTA_WPARAM(_wparam) > 0 ? +1.0f : -1.0f;
            return true;
        case WM_MOUSEMOVE:
            imgui.MousePos.x = (signed short)(_lparam);
            imgui.MousePos.y = (signed short)(_lparam >> 16);
            return true;
        case WM_KEYDOWN:
            if (_wparam < 256)
                imgui.KeysDown[_wparam] = 1;
            return true;
        case WM_KEYUP:
            if (_wparam < 256)
                imgui.KeysDown[_wparam] = 0;
            return true;
        case WM_CHAR:
            // You can also use ToAscii()+GetKeyboardState() to retrieve characters.
            if (_wparam > 0 && _wparam < 0x10000)
                imgui.AddInputCharacter((unsigned short)_wparam);
            return true;
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

namespace render
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
        RECT rect;
        GetClientRect(hwnd, &rect);
        float w = (float)(rect.right - rect.left);
        float h = (float)(rect.bottom - rect.top);

        if (GetWidth() != w || GetHeight() != h)
        {
            SetWidth(w);
            SetHeight(h);
            CDevice& lDevice = helios::CEngine::GetInstance().GetDevice();
            lDevice.SetBackBufferWidth(w);
            lDevice.SetBackBufferHeight(h);
            lDevice.Reset();
        }

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