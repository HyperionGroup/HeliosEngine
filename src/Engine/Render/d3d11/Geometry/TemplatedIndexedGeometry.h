#ifndef __CIndexedRenderableVertexs_HH__
#define __CIndexedRenderableVertexs_HH__

#pragma once

#include "Geometry.h"

namespace render
{
    template < typename TVertexType, typename TIndexType, typename TPrimitiveTopology >
    class CTemplatedIndexedGeometry : public CGeometry<TPrimitiveTopology>
    {
    public:
        CTemplatedIndexedGeometry(CVertexBuffer< TVertexType >* aVertexBuffer, CIndexBuffer* aIndexBuffer)
            : CGeometry()
            , m_VertexBuffer(aVertexBuffer)
            , m_IndexBuffer(aIndexBuffer)
        {
        }

        virtual ~CTemplatedIndexedGeometry()
        {
            delete m_VertexBuffer;
            delete m_IndexBuffer;
        }

        virtual void RenderIndexed(CDevicePtr _device, uint32 IndexCount = -1, uint32 StartIndexLocation = 0, uint32 BaseVertexLocation = 0)
        {
            CGeometry::Render(_device);
            m_VertexBuffer->Bind(_device);
            m_IndexBuffer->Bind(_device);
            _device->ImmediateContext()->DrawIndexed(m_IndexBuffer->GetIndexCount(), StartIndexLocation, BaseVertexLocation);
        }

    private:
        CIndexBuffer<TIndexType>*  m_IndexBuffer;
        CVertexBuffer<TVertexType> * m_VertexBuffer;
    };
}

#endif // _TEMPLATED_RENDERABLE_VERTEXS_HH_
