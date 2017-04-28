//=================================================================================================
//
//  MJP's DX11 Sample Framework
//  http://mynameismjp.wordpress.com/
//
//  All code and content licensed under Microsoft Public License (Ms-PL)
//
//=================================================================================================

#include "Device.h"

using std::wstring;

namespace render
{
    CDevice::CDevice()
        : backBufferFormat(DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM),
        backBufferWidth(1280),
        backBufferHeight(720),
        msCount(1),
        msQuality(0),
        enableAutoDS(true),
        fullScreen(false),
        featureLevel(D3D_FEATURE_LEVEL_11_1),
        minFeatureLevel(D3D_FEATURE_LEVEL_10_0),
        autoDSFormat(DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT),
        useAutoDSAsSR(false),
        vsync(true),
        numVSYNCIntervals(1)
    {
        refreshRate.Numerator = 60;
        refreshRate.Denominator = 1;
    }

    CDevice::~CDevice()
    {
        if (immediateContext)
        {
            immediateContext->ClearState();
            immediateContext->Flush();
        }
    }

    void CDevice::Initialize(HWND outputWindow)
    {
        CheckForSuitableOutput();

        DXGI_SWAP_CHAIN_DESC desc;
        ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

        if (fullScreen)
            PrepareFullScreenSettings();
        else
        {
            refreshRate.Numerator = 60;
            refreshRate.Denominator = 1;
        }

        desc.BufferCount = 2;
        desc.BufferDesc.Format = backBufferFormat;
        desc.BufferDesc.Width = backBufferWidth;
        desc.BufferDesc.Height = backBufferHeight;
        desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        desc.BufferDesc.RefreshRate = refreshRate;
        desc.SampleDesc.Count = msCount;
        desc.SampleDesc.Quality = msQuality;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        desc.OutputWindow = outputWindow;
        desc.Windowed = !fullScreen;

        UINT flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#ifdef _DEBUG
        flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        DXCall(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flags,
            NULL, 0, D3D11_SDK_VERSION, &desc, &swapChain, &device, NULL, &immediateContext));

        featureLevel = device->GetFeatureLevel();

        if (featureLevel < minFeatureLevel)
        {
            wstring majorLevel = std::to_wstring(minFeatureLevel >> 12);
            wstring minorLevel = std::to_wstring(( minFeatureLevel >> 8) & 0xF );
            LOG_ERROR_APPLICATION("The device doesn't support the minimum feature level required to run this sample (DX %d.%2 )", majorLevel, minorLevel );
        }

        // Query the current feature level:
        switch (featureLevel)
        {
        case D3D_FEATURE_LEVEL_11_1:
        case D3D_FEATURE_LEVEL_11_0:
        {
            mVSFeatureLevel = "vs_5_0";
            mPSFeatureLevel = "ps_5_0";
        }
        break;
        case D3D_FEATURE_LEVEL_10_1:
        {
            mVSFeatureLevel = "vs_4_1";
            mPSFeatureLevel = "ps_4_1";
        }
        break;
        case D3D_FEATURE_LEVEL_10_0:
        {
            mVSFeatureLevel = "vs_4_0";
            mPSFeatureLevel = "ps_4_0";
        }
        break;
        case D3D_FEATURE_LEVEL_9_3:
        {
            mVSFeatureLevel = "vs_4_0_level_9_3";
            mPSFeatureLevel = "ps_4_0_level_9_3";
        }
        break;
        case D3D_FEATURE_LEVEL_9_2:
        case D3D_FEATURE_LEVEL_9_1:
        {
            mVSFeatureLevel = "vs_4_0_level_9_1";
            mPSFeatureLevel = "ps_4_0_level_9_1";
        }
        break;
        } // switch( featureLevel )

        AfterReset();
    }

    void CDevice::AfterReset()
    {
        DXGI_SWAP_CHAIN_DESC sd;
        swapChain->GetDesc(&sd);
        DXCall(swapChain->GetBuffer(0, __uuidof(bbTexture), reinterpret_cast<void**>(&bbTexture)));

        D3D11_RENDER_TARGET_VIEW_DESC render_target_view_desc;
        ZeroMemory(&render_target_view_desc, sizeof(render_target_view_desc));
        render_target_view_desc.Format = sd.BufferDesc.Format;
        render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        DXCall(device->CreateRenderTargetView(bbTexture, &render_target_view_desc, &bbRTView));

        // Create a default DepthStencil buffer
        if (enableAutoDS)
        {
            UINT bindFlags = D3D11_BIND_DEPTH_STENCIL;
            if (useAutoDSAsSR)
                bindFlags |= D3D11_BIND_SHADER_RESOURCE;

            DXGI_FORMAT dsTexFormat;
            if (!useAutoDSAsSR)
                dsTexFormat = autoDSFormat;
            else if (autoDSFormat == DXGI_FORMAT_D16_UNORM)
                dsTexFormat = DXGI_FORMAT_R16_TYPELESS;
            else if (autoDSFormat == DXGI_FORMAT_D24_UNORM_S8_UINT)
                dsTexFormat = DXGI_FORMAT_R24G8_TYPELESS;
            else
                dsTexFormat = DXGI_FORMAT_R32_TYPELESS;

            D3D11_TEXTURE2D_DESC dsDesc;
            dsDesc.Width = backBufferWidth;
            dsDesc.Height = backBufferHeight;
            dsDesc.ArraySize = 1;
            dsDesc.BindFlags = bindFlags;
            dsDesc.CPUAccessFlags = 0;
            dsDesc.Format = dsTexFormat;
            dsDesc.MipLevels = 1;
            dsDesc.MiscFlags = 0;
            dsDesc.SampleDesc.Count = msCount;
            dsDesc.SampleDesc.Quality = msQuality;
            dsDesc.Usage = D3D11_USAGE_DEFAULT;
            DXCall(device->CreateTexture2D(&dsDesc, NULL, &autoDSTexture));

            D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
            dsvDesc.Format = autoDSFormat;
            dsvDesc.ViewDimension = msCount > 1 ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;;
            dsvDesc.Texture2D.MipSlice = 0;
            dsvDesc.Flags = 0;
            DXCall(device->CreateDepthStencilView(autoDSTexture, &dsvDesc, &autoDSView));

            if (useAutoDSAsSR)
            {
                DXGI_FORMAT dsSRVFormat;
                if (autoDSFormat == DXGI_FORMAT_D16_UNORM)
                    dsSRVFormat = DXGI_FORMAT_R16_UNORM;
                else if (autoDSFormat == DXGI_FORMAT_D24_UNORM_S8_UINT)
                    dsSRVFormat = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
                else
                    dsSRVFormat = DXGI_FORMAT_R32_FLOAT;

                D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
                srvDesc.Format = dsSRVFormat;
                srvDesc.ViewDimension = msCount > 1 ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
                srvDesc.Texture2D.MipLevels = 1;
                srvDesc.Texture2D.MostDetailedMip = 0;
                DXCall(device->CreateShaderResourceView(autoDSTexture, &srvDesc, &autoDSSRView));
            }
            else
                autoDSSRView = NULL;
        }

        // Set default render targets
        immediateContext->OMSetRenderTargets(1, &(bbRTView.GetInterfacePtr()), autoDSView);

        // Setup the viewport
        D3D11_VIEWPORT vp;
        vp.Width = static_cast<float>(backBufferWidth);
        vp.Height = static_cast<float>(backBufferHeight);
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        immediateContext->RSSetViewports(1, &vp);
    }

    void CDevice::CheckForSuitableOutput()
    {
        HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&factory));
        if (FAILED(hr))
            LOG_ERROR_APPLICATION("Unable to create a DXGI 1.1 device.\n Make sure your OS and driver support DirectX 11");

        // Look for an adapter that supports D3D11
        IDXGIAdapter1Ptr curAdapter;
        UINT adapterIdx = 0;
        LARGE_INTEGER umdVersion;
        while (!adapter && SUCCEEDED(factory->EnumAdapters1(0, &adapter)))
            if (SUCCEEDED(adapter->CheckInterfaceSupport(__uuidof(ID3D11Device), &umdVersion)))
                adapter = curAdapter;

        if (!adapter)
            LOG_ERROR_APPLICATION("Unable to locate a DXGI 1.1 adapter that supports a D3D11 device.\n Make sure your OS and driver support DirectX 11");

        // We'll just use the first output
        DXCall(adapter->EnumOutputs(0, &output));
    }

    void CDevice::PrepareFullScreenSettings()
    {
        _ASSERT(output);

        // Have the Output look for the closest matching mode
        DXGI_MODE_DESC desiredMode;
        desiredMode.Format = backBufferFormat;
        desiredMode.Width = backBufferWidth;
        desiredMode.Height = backBufferHeight;
        desiredMode.RefreshRate.Numerator = 0;
        desiredMode.RefreshRate.Denominator = 0;
        desiredMode.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        desiredMode.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

        DXGI_MODE_DESC closestMatch;
        DXCall(output->FindClosestMatchingMode(&desiredMode, &closestMatch, device.GetInterfacePtr()));

        backBufferFormat = closestMatch.Format;
        backBufferWidth = closestMatch.Width;
        backBufferHeight = closestMatch.Height;
        refreshRate = closestMatch.RefreshRate;
    }

    void CDevice::Reset()
    {
        _ASSERT(swapChain);

        // Release all references
        if (bbTexture)
            bbTexture.Release();

        if (bbRTView)
            bbRTView.Release();

        if (autoDSTexture)
            autoDSTexture.Release();

        if (autoDSView)
            autoDSView.Release();

        if (autoDSSRView)
            autoDSSRView.Release();

        immediateContext->ClearState();

        if (fullScreen)
            PrepareFullScreenSettings();
        else
        {
            refreshRate.Numerator = 60;
            refreshRate.Denominator = 1;
        }

        DXCall(swapChain->SetFullscreenState(fullScreen, NULL));

        DXCall(swapChain->ResizeBuffers(2, backBufferWidth, backBufferHeight, backBufferFormat, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));

        if (fullScreen)
        {
            DXGI_MODE_DESC mode;
            mode.Format = backBufferFormat;
            mode.Width = backBufferWidth;
            mode.Height = backBufferHeight;
            mode.RefreshRate.Numerator = 0;
            mode.RefreshRate.Denominator = 0;
            mode.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
            mode.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
            DXCall(swapChain->ResizeTarget(&mode));
        }

        AfterReset();
    }

    void CDevice::Present()
    {
        _ASSERT(device);

        UINT interval = vsync ? numVSYNCIntervals : 0;
        DXCall(swapChain->Present(interval, 0));
    }

}