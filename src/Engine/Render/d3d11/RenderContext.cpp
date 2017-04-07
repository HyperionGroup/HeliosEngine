#include "RenderContext.h"

namespace render
{
    CRenderContext::CRenderContext()
        : mSwapChain(nullptr)
        , mDevice(nullptr)
        , mContext(nullptr)
        , mRenderTargetView(nullptr)
        , mDepthStencil(nullptr)
        , mDebug(nullptr)
    {
    }

    CRenderContext::~CRenderContext()
    {
        CHECKED_RELEASE(mSwapChain);
        CHECKED_RELEASE(mDevice);
        CHECKED_RELEASE(mContext);
        CHECKED_RELEASE(mRenderTargetView);
        CHECKED_RELEASE(mDepthStencil);
        CHECKED_RELEASE(mDepthStencilView);
#ifdef _DEBUG
        mDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
        CHECKED_RELEASE(mDebug);
#endif
    }

    bool CRenderContext::CreateContext(HWND _hwnd)
    {
        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
        };

        UINT numFeatureLevels = ARRAYSIZE(featureLevels);

        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 1;
        sd.BufferDesc.Width = 800;
        sd.BufferDesc.Height = 600;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = _hwnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

#ifdef _DEBUG
        HRESULT lHR = D3D11CreateDeviceAndSwapChain(NULL,
            D3D_DRIVER_TYPE_HARDWARE,
            NULL,
            D3D11_CREATE_DEVICE_DEBUG,
            featureLevels,
            numFeatureLevels,
            D3D11_SDK_VERSION,
            &sd,
            &mSwapChain,
            &mDevice,
            NULL,
            &mContext);

        if (FAILED(lHR))
            return false;

        lHR = mDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&mDebug));
        if (!mDebug)
            return false;
#else
        HRESULT lHR = D3D11CreateDeviceAndSwapChain(NULL,
            D3D_DRIVER_TYPE_HARDWARE,
            NULL,
            0,
            featureLevels,
            numFeatureLevels,
            D3D11_SDK_VERSION,
            &sd,
            &mSwapChain,
            &mDevice,
            NULL,
            &mContext);

        if (FAILED(lHR))
            return false;
#endif
        return Resize(800, 600);
    }

    void CRenderContext::ClearColor(float* _color)
    {
        mContext->ClearRenderTargetView(mRenderTargetView, _color);
    }

    void CRenderContext::SwapBuffers()
    {
        mSwapChain->Present(1,0);
    }

    bool CRenderContext::Resize(uint32 _w, uint32 _h)
    {
        mContext->OMSetRenderTargets(0, nullptr, nullptr);
        CHECKED_RELEASE(mRenderTargetView);
        CHECKED_RELEASE(mDepthStencil);
        CHECKED_RELEASE(mDepthStencilView);

        mSwapChain->ResizeBuffers(0, _w, _h, DXGI_FORMAT_UNKNOWN, 0);

        ID3D11Texture2D *pBackBuffer;
        if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer)))
            return false;

        HRESULT hr = mDevice->CreateRenderTargetView(pBackBuffer, NULL, &mRenderTargetView);
        pBackBuffer->Release();

        if (FAILED(hr) || !mRenderTargetView)
            return false;

        D3D11_TEXTURE2D_DESC descDepth;
        ZeroMemory(&descDepth, sizeof(descDepth));
        descDepth.Width = _w;
        descDepth.Height = _h;
        descDepth.MipLevels = 1;
        descDepth.ArraySize = 1;
        descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        descDepth.SampleDesc.Count = 1;
        descDepth.SampleDesc.Quality = 0;
        descDepth.Usage = D3D11_USAGE_DEFAULT;
        descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        descDepth.CPUAccessFlags = 0;
        descDepth.MiscFlags = 0;
        hr = mDevice->CreateTexture2D(&descDepth, NULL, &mDepthStencil);
        if (FAILED(hr))
            return false;

        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
        ZeroMemory(&descDSV, sizeof(descDSV));
        descDSV.Format = descDepth.Format;
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        descDSV.Texture2D.MipSlice = 0;
        hr = mDevice->CreateDepthStencilView(mDepthStencil, &descDSV, &mDepthStencilView);
        if (FAILED(hr))
            return false;

        mContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

        mViewport.Width = (FLOAT)_w;
        mViewport.Height = (FLOAT)_h;
        mViewport.MinDepth = 0.0f;
        mViewport.MaxDepth = 1.0f;
        mViewport.TopLeftX = 0;
        mViewport.TopLeftY = 0;
        mContext->RSSetViewports(1, &mViewport);

        return true;
    }
}