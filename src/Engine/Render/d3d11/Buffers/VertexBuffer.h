#ifndef __VERTEX_BUFFER__HH__
#define __VERTEX_BUFFER__HH__
#pragma once

#include "Buffer.h"

namespace render
{
    template< class TVertexType >
    class CVertexBuffer : public CBuffer
    {
    public:
        void * mRawData;
    public:
        CVertexBuffer(CRenderManager& RenderManager, void* aRawData, uint32 aNumVertexs)
            : mNumVertexs(aNumVertexs)
            , mRawData(nullptr)
        {
        }

        virtual ~CVertexBuffer()
        {
            free(mRawData);
        }

        void Initialize(CDevicePtr _device)
        {
            HELIOSASSERT(mRawData);

            D3D11_BUFFER_DESC lVB;
            ZeroMemory(&lVB, sizeof(lVB));
            lVB.Usage = D3D11_USAGE_DEFAULT;
            lVB.ByteWidth = sizeof(TVertexType)*mNumVertexs;
            lVB.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            lVB.CPUAccessFlags = 0;

            D3D11_SUBRESOURCE_DATA lSubresourceData;
            ZeroMemory(&lSubresourceData, sizeof(lSubresourceData));
            lSubresourceData.pSysMem = mRawData;

            DXCall(_device->Device()->CreateBuffer(&lVB, &lSubresourceData, &mBuffer) );

            mInitialized = true;
        }

        virtual void Bind(CDevicePtr _device)
        {
            uint32 offset = 0, stride = GetStride();
            _device->ImmediateContext()->IASetVertexBuffers(0, 1, &mBuffer, &stride, &offset);
        }

        inline uint32 GetNumVertexs() const { return mNumVertexs; }
        inline uint32 GetStride() const { return sizeof(TVertexType); }

    protected:
        uint32 mNumVertexs;
    };
}
#endif
