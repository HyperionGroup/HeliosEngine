#ifndef _RENDER_CONTEXT_H_
#define _RENDER_CONTEXT_H_

#pragma once

#include "Render.h"
#include "Singleton.h"

namespace render
{
    class CRenderContext : public core::CSingleton<CRenderContext>
    {
    private:
        IDXGISwapChain *        mSwapChain;
        ID3D11Device*           mDevice;
        ID3D11DeviceContext*    mContext;
        ID3D11RenderTargetView* mRenderTargetView;
        ID3D11Texture2D*        mDepthStencil;
        ID3D11DepthStencilView*	mDepthStencilView;
        D3D11_VIEWPORT          mViewport;
#ifdef _DEBUG
        ID3D11Debug*            mDebug;
#endif
    public:
        CRenderContext();
        virtual ~CRenderContext();
        bool CreateContext(HWND _hwnd);
        void ClearColor(float* _color);
        void SwapBuffers();
        bool Resize(uint32 _w, uint32 _h);

        ID3D11Device *        GetDevice() const { return mDevice; }
        ID3D11DeviceContext * GetContext() const { return mContext; }
        IDXGISwapChain*       GetSwapChain() { return mSwapChain; }
    };
}

#endif 