//=================================================================================================
//
//	MJP's DX11 Sample Framework
//  http://mynameismjp.wordpress.com/
//
//  All code and content licensed under Microsoft Public License (Ms-PL)
//
//=================================================================================================

#pragma once

#include "Singleton.h"
#include "States.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;
struct ID3D11Texture2D;
struct ID3D11DepthStencilView;
struct ID3D11ShaderResourceView;

namespace render
{
    class CDevice : public core::CSingleton< CDevice >
    {
    public:

        CDevice();
        ~CDevice();

        void Initialize(HWND outputWindow);
        void Reset();
        void Present();

        // Getters
        inline ID3D11Device*              Device() const { return device.GetInterfacePtr(); };
        inline ID3D11DeviceContext*       ImmediateContext() const { return immediateContext.GetInterfacePtr(); };
        inline IDXGISwapChain*            SwapChain() const { return swapChain.GetInterfacePtr(); };
        inline ID3D11RenderTargetView*    BackBuffer() const { return bbRTView.GetInterfacePtr(); };
        inline ID3D11Texture2D*           BackBufferTexture() const { return bbTexture; };
        inline ID3D11DepthStencilView*    AutoDepthStencilView() const { return autoDSView; };
        inline ID3D11ShaderResourceView*  AutoDepthStencilSRView() const { return autoDSSRView; };
        inline D3D_FEATURE_LEVEL          FeatureLevel() const { return featureLevel; };
        inline D3D_FEATURE_LEVEL          MinFeatureLevel() const { return minFeatureLevel; };

        DXGI_FORMAT		BackBufferFormat() const { return backBufferFormat; };
        UINT			BackBufferWidth() const { return backBufferWidth; };
        UINT			BackBufferHeight() const { return backBufferHeight; };
        UINT			BackBufferMSCount() const { return msCount; };
        UINT			BackBufferMSQuality() const { return msQuality; };
        bool			AutoDepthStencilEnabled() const { return enableAutoDS; };
        DXGI_FORMAT		AutoDepthStencilFormat() const { return autoDSFormat; };
        bool            UseAutoDepthStencilAsSR() const { return useAutoDSAsSR; };
        bool			FullScreen() const { return fullScreen; };
        bool			VSYNCEnabled() const { return vsync; };
        UINT            NumVSYNCIntervals() const { return numVSYNCIntervals; };

        const char*     GetVertexStageFeatureLevel() const { return mVSFeatureLevel; }
        const char*     GetPixelStageFeatureLevel() const { return mPSFeatureLevel; }
        const char*     GetGeometryStageFeatureLevel() const { return mGSFeatureLevel; }


        // Setters
        void SetBackBufferFormat(DXGI_FORMAT format) { backBufferFormat = format; };
        void SetBackBufferWidth(UINT width) { backBufferWidth = width; };
        void SetBackBufferHeight(UINT height) { backBufferHeight = height; };
        void SetBackBufferMSCount(UINT count) { msCount = count; };
        void SetBackBufferMSQuality(UINT quality) { msQuality = quality; };
        void SetAutoDepthStencilEnabled(bool enabled) { enableAutoDS = enabled; };
        void SetAutoDepthStencilFormat(DXGI_FORMAT fmt) { autoDSFormat = fmt; };
        void SetUseAutoDSAsSR(bool useAsSR) { useAutoDSAsSR = useAsSR; };
        void SetFullScreen(bool enabled) { fullScreen = enabled; };
        void SetVSYNCEnabled(bool enabled) { vsync = enabled; };
        void SetMinFeatureLevel(D3D_FEATURE_LEVEL level) { minFeatureLevel = level; };
        void SetNumVSYNCIntervals(UINT intervals) { numVSYNCIntervals = intervals; };

        void SetBlendState(BlendState _state, float* _blendFactor = nullptr);
        void SetRasterizerState(RasterizerState _state);
        void SetDepthStencilState(DepthStencilState _state);

        void SetViewport(float _topLeftX, float _topLeftY, float _w, float _h);
        void ResetViewport();

    protected:

        void CheckForSuitableOutput();
        void AfterReset();
        void PrepareFullScreenSettings();

        IDXGIFactory1Ptr                factory;
        IDXGIAdapter1Ptr                adapter;
        IDXGIOutputPtr                  output;

        ID3D11DevicePtr					device;
        ID3D11DeviceContextPtr			immediateContext;
        IDXGISwapChainPtr				swapChain;
        ID3D11Texture2DPtr				bbTexture;
        ID3D11RenderTargetViewPtr		bbRTView;

        DXGI_FORMAT					backBufferFormat;
        UINT						backBufferWidth;
        UINT						backBufferHeight;
        UINT						msCount;
        UINT						msQuality;
        bool						enableAutoDS;
        ID3D11Texture2DPtr			autoDSTexture;
        ID3D11DepthStencilViewPtr   autoDSView;
        DXGI_FORMAT					autoDSFormat;
        ID3D11ShaderResourceViewPtr autoDSSRView;
        bool                        useAutoDSAsSR;
        bool						fullScreen;
        bool						vsync;
        DXGI_RATIONAL               refreshRate;
        UINT                        numVSYNCIntervals;

        D3D_FEATURE_LEVEL			featureLevel;
        D3D_FEATURE_LEVEL           minFeatureLevel;

        BlendStates                 mBlendState;
        RasterizerStates            mRasterizerState;
        DepthStencilStates          mDepthStencilState;

        const char* mVSFeatureLevel;
        const char* mPSFeatureLevel;
        const char* mGSFeatureLevel;
    };

}