#ifndef __CONSTANT_BUFFER__HH__
#define __CONSTANT_BUFFER__HH__
#pragma once

#include "Buffer.h"

// https://developer.nvidia.com/content/constant-buffers-without-constant-pain-0

namespace render
{
    template<typename T>
    class CConstantBuffer : public CBuffer
    {
    public:
        T Data;
    public:
        CConstantBuffer()
            : CBuffer()
        {
            ZeroMemory(&Data, sizeof(T));
        }

        virtual void Bind(CDevicePtr _device)
        {
            HELIOSUNUSED(_device);
            assert("This method must not be called!");
        }

        void Initialize(CDevicePtr _device)
        {
            D3D11_BUFFER_DESC desc;
            desc.Usage = D3D11_USAGE_DYNAMIC;
            desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            desc.MiscFlags = 0;
            desc.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16)));
            DXCall(_device->Device()->CreateBuffer(&desc, NULL, &mBuffer));
            mInitialized = true;
        }

        void ApplyChanges(CDevicePtr _device)
        {
            HELIOSASSERT(mInitialized);
            D3D11_MAPPED_SUBRESOURCE mappedResource;
            DXCall(_device->ImmediateContext()->Map(mBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));
            CopyMemory(mappedResource.pData, &Data, sizeof(T));
            _device->ImmediateContext()->Unmap(mBuffer, 0);
        }

        void BindVS(CDevicePtr _device, UINT slot) const
        {
            HELIOSASSERT(mInitialized);
            ID3D11Buffer* bufferArray[1];
            bufferArray[0] = mBuffer;
            _device->ImmediateContext()->VSSetConstantBuffers(slot, 1, bufferArray);
        }

        void BindPS(CDevicePtr _device, UINT slot) const
        {
            HELIOSASSERT(mInitialized);
            ID3D11Buffer* bufferArray[1];
            bufferArray[0] = mBuffer;
            _device->ImmediateContext()->PSSetConstantBuffers(slot, 1, bufferArray);
        }

        void BindGS(CDevicePtr _device, UINT slot) const
        {
            HELIOSASSERT(mInitialized);
            ID3D11Buffer* bufferArray[1];
            bufferArray[0] = mBuffer;
            _device->ImmediateContext()->GSSetConstantBuffers(slot, 1, bufferArray);
        }

        void BindHS(CDevicePtr _device, UINT slot) const
        {
            HELIOSASSERT(mInitialized);
            ID3D11Buffer* bufferArray[1];
            bufferArray[0] = mBuffer;
            _device->ImmediateContext()->HSSetConstantBuffers(slot, 1, bufferArray);
        }

        void BindDS(CDevicePtr _device, UINT slot) const
        {
            HELIOSASSERT(mInitialized);
            ID3D11Buffer* bufferArray[1];
            bufferArray[0] = mBuffer;
            _device->ImmediateContext()->DSSetConstantBuffers(slot, 1, bufferArray);
        }

        void BindCS(CDevicePtr _device, UINT slot) const
        {
            HELIOSASSERT(mInitialized);
            ID3D11Buffer* bufferArray[1];
            bufferArray[0] = buffer;
            _device->ImmediateContext()->CSSetConstantBuffers(slot, 1, bufferArray);
        }
    };

#endif
