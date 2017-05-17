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
        CVertexBuffer()
            : CBuffer()
            , mNumVertexs(0u)
        {
        }

        virtual ~CVertexBuffer()
        {
            mNumVertexs = 0u;
        }

        void Initialize(ID3D11DevicePtr _device, const TVertexType * _data )
        {
            HELIOSASSERT(!mInitialized);
            HELIOSASSERT(_data);

            D3D11_BUFFER_DESC lVB;
            ZeroMemory(&lVB, sizeof(lVB));
            lVB.Usage = mUsage;
            lVB.ByteWidth = sizeof(TVertexType)*mNumVertexs;
            lVB.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            lVB.CPUAccessFlags = 0;

            D3D11_SUBRESOURCE_DATA lSubresourceData;
            ZeroMemory(&lSubresourceData, sizeof(lSubresourceData));
            lSubresourceData.pSysMem = _data;

            DXCall(_device->CreateBuffer(&lVB, &lSubresourceData, &mBuffer) );

            mInitialized = true;
        }

        virtual void Bind(ID3D11DeviceContextPtr _device)
        {
            uint32 offset = 0, stride = GetStride();
            _device->IASetVertexBuffers(0, 1, &mBuffer, &stride, &offset);
        }

        inline uint32 GetNumVertexs() const { return mNumVertexs; }
        inline void   SetNumVertexs(uint32 _numVertex) { mNumVertexs = _numVertex; }
        inline uint32 GetStride() const { return sizeof(TVertexType); }
     protected:
        uint32        mNumVertexs;
    };
}
#endif
