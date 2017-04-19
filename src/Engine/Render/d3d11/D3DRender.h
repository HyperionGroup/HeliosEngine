#pragma once

#ifdef _DEBUG
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

#include <dxgi.h>
#include <D3Dcompiler.h>
#include <D3dcsx.h>

#include <windows.h>
#include <comdef.h>

#include <dxgi.h>

#include <d3d9.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11_2.h>

#include <d3dcompiler.h>

#include <wrl/client.h>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#define COM_SMARTPTR(classname) _COM_SMARTPTR_TYPEDEF(classname, __uuidof(classname));

COM_SMARTPTR(ID3D11Device)
COM_SMARTPTR(IDXGIFactory1)
COM_SMARTPTR(IDXGIAdapter1)
COM_SMARTPTR(IDXGIOutput)
COM_SMARTPTR(ID3D11DeviceContext)
COM_SMARTPTR(IDXGISwapChain)
COM_SMARTPTR(ID3D11Texture2D)
COM_SMARTPTR(ID3D11RenderTargetView)
COM_SMARTPTR(ID3D11DepthStencilView)
COM_SMARTPTR(ID3D11ShaderResourceView)
COM_SMARTPTR(ID3D11BlendState)
COM_SMARTPTR(ID3D11RasterizerState)
COM_SMARTPTR(ID3D11DepthStencilState)
COM_SMARTPTR(ID3D11SamplerState)

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "D3D9.lib")
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "gdiplus.lib")

#define RENDER_API d3d11
inline void DXCall(HRESULT hr)
{
#if DX_LOG_CALLS
#define D3D_ERROR_CASE(HR_ERROR) case HR_ERROR: lMsg = #HR_ERROR; break;
    std::string lMsg;
    if (FAILED(hr))
    {
        switch (hr)
        {
            D3D_ERROR_CASE(D3D11_ERROR_FILE_NOT_FOUND)
            D3D_ERROR_CASE(D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS)
            D3D_ERROR_CASE(D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS)
            D3D_ERROR_CASE(D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD)
            D3D_ERROR_CASE(DXGI_ERROR_INVALID_CALL)
            D3D_ERROR_CASE(DXGI_ERROR_WAS_STILL_DRAWING)
            D3D_ERROR_CASE(E_FAIL)
            D3D_ERROR_CASE(E_INVALIDARG)
            D3D_ERROR_CASE(E_OUTOFMEMORY)
            D3D_ERROR_CASE(E_NOTIMPL)
            D3D_ERROR_CASE(S_FALSE)
        default:
            break;
        }
        LOG_ERROR_APPLICATION("Error calling render function %s", lMsg.c_str());
    }

#undef D3D_ERROR_CASE
#endif
}