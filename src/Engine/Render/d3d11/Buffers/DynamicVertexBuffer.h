#ifndef __DVERTEX_BUFFER__HH__
#define __DVERTEX_BUFFER__HH__
#pragma once

#include "VertexBuffer.h"

namespace render
{
    template< class TVertexType >
    class CDynamicVertexBuffer : public CVertexBuffer< TVertexType >
    {
    public:
        CDynamicVertexBuffer()
            : CVertexBuffer()
        {
            mUsage = D3D11_USAGE_DYNAMIC;
        }

        virtual ~CDynamicVertexBuffer()
        {
        }

        void Apply(ID3D11DeviceContextPtr _device, const TVertexType * _data )
        {
            HELIOSASSERT(mInitialized);
            D3D11_MAPPED_SUBRESOURCE mappedResource;
            DXCall(_device->Map(mBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));
            CopyMemory(mappedResource.pData, &_data, sizeof(TVertexType)*mNumVertexs);
            _device->Unmap(mBuffer, 0);
        }
    };
}
#endif
