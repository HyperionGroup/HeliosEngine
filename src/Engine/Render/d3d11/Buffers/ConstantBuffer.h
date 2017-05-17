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

        virtual void Bind(ID3D11DeviceContextPtr _device)
        {
            HELIOSUNUSED(_device);
            assert("This method must not be called!");
        }

        void Initialize(ID3D11DevicePtr _device)
        {
            HELIOSASSERT(!mInitialized);

            D3D11_BUFFER_DESC desc;
            desc.Usage = mUsage;
            desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            desc.MiscFlags = 0;
            desc.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16)));
            DXCall(_device->CreateBuffer(&desc, NULL, &mBuffer));
            mInitialized = true;
        }

        void Apply(ID3D11DeviceContextPtr _device)
        {
            HELIOSASSERT(mInitialized);
            D3D11_MAPPED_SUBRESOURCE mappedResource;
            DXCall(_device->Map(mBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));
            CopyMemory(mappedResource.pData, &Data, sizeof(T));
            _device->Unmap(mBuffer, 0);
        }

        void BindVS(ID3D11DeviceContextPtr _device, UINT slot) const
        {
            HELIOSASSERT(mInitialized);
            ID3D11Buffer* bufferArray[1];
            bufferArray[0] = mBuffer;
            _device->VSSetConstantBuffers(slot, 1, bufferArray);
        }

        void BindPS(ID3D11DeviceContextPtr _device, UINT slot) const
        {
            HELIOSASSERT(mInitialized);
            ID3D11Buffer* bufferArray[1];
            bufferArray[0] = mBuffer;
            _device->PSSetConstantBuffers(slot, 1, bufferArray);
        }

        void BindGS(ID3D11DeviceContextPtr _device, UINT slot) const
        {
            HELIOSASSERT(mInitialized);
            ID3D11Buffer* bufferArray[1];
            bufferArray[0] = mBuffer;
            _device->GSSetConstantBuffers(slot, 1, bufferArray);
        }

        void BindHS(ID3D11DeviceContextPtr _device, UINT slot) const
        {
            HELIOSASSERT(mInitialized);
            ID3D11Buffer* bufferArray[1];
            bufferArray[0] = mBuffer;
            _device->HSSetConstantBuffers(slot, 1, bufferArray);
        }

        void BindDS(ID3D11DeviceContext* _device, UINT slot) const
        {
            HELIOSASSERT(mInitialized);
            ID3D11Buffer* bufferArray[1];
            bufferArray[0] = mBuffer;
            _device->DSSetConstantBuffers(slot, 1, bufferArray);
        }

        void BindCS(ID3D11DeviceContextPtr _device, UINT slot) const
        {
            HELIOSASSERT(mInitialized);
            ID3D11Buffer* bufferArray[1];
            bufferArray[0] = buffer;
            _device->CSSetConstantBuffers(slot, 1, bufferArray);
        }
    };
}

#endif
