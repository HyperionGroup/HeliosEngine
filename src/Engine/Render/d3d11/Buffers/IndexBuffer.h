#ifndef __INDEX_BUFFER__HH__
#define __INDEX_BUFFER__HH__
#pragma once

#include "Buffer.h"

namespace render
{
    template<typename TIndexType>
    class CIndexBuffer : public CBuffer
    {
    public:
        void* mRawData;
    public:
        CIndexBuffer(uint32 aNumIndices)
            : mNumIndices(0)
            , mRawData(nullptr)
        {
        }

        virtual ~CIndexBuffer()
        {
            free(mRawData);
        }

        virtual void Bind(CDevicePtr _device);

        void Initialize(CDevicePtr _device)
        {
            HELIOSASSERT(mRawData);

            D3D11_BUFFER_DESC lIB;
            ZeroMemory(&lIB, sizeof(lIB));
            lIB.Usage = D3D11_USAGE_DEFAULT;
            lIB.ByteWidth = sizeof(TIndexType) * mNumIndices;
            lIB.BindFlags = D3D11_BIND_INDEX_BUFFER;
            lIB.CPUAccessFlags = 0;

            D3D11_SUBRESOURCE_DATA lSubresourceData;
            ZeroMemory(&lSubresourceData, sizeof(lSubresourceData));
            lSubresourceData.pSysMem = mRawData;

            DXCall(_device->Device()->CreateBuffer(&lIB, &lSubresourceData, &mBuffer));

            mInitialized = true;
        }

        inline uint32 GetIndexCount() const { return mNumIndices; }
        inline void SetIndexCount(uint32 _numIndices) { mNumIndices = _numIndices; }

    protected:
        uint32 mNumIndices;
    };

    template <>
    void CIndexBuffer<uint16>::Bind(CDevicePtr _device)
    {
        HELIOSASSERT(mInitialized);
        _device->ImmediateContext()->IASetIndexBuffer(mBuffer, DXGI_FORMAT_R16_UINT, 0);
    }

    template <>
    void CIndexBuffer<uint32>::Bind(CDevicePtr _device)
    {
        HELIOSASSERT(mInitialized);
        _device->ImmediateContext()->IASetIndexBuffer(mBuffer, DXGI_FORMAT_R32_UINT, 0);
    }
}

#endif // _BUFFER_HH_
