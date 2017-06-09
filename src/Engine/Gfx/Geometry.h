#pragma once
#include "Gfx.h"
#include "Vertex.h"
#include "Buffer.h"

namespace render
{
    class CGeometry
    {
    public:
        CGeometry()  {}
        virtual ~CGeometry() {}

        virtual void Render()
        {
            
        }

        virtual void RenderIndexed(uint32 _indexCount = -1, uint32 _startIndexLocation = 0, uint32 _baseVertexLocation = 0)
        {
            
        }

    protected:

    };

    template< class TVertexType >
    class CTemplatedGeometry : public CGeometry
    {
    public:
        CTemplatedGeometry( std::shared_ptr< CVertexBuffer<TVertexType> > VertexBuffer)
            : CGeometry()
            , m_VertexBuffer(VertexBuffer)
        {
        }

        virtual ~CTemplatedGeometry()
        {
        }

        virtual void Render(ID3D11DeviceContextPtr _device)
        {
            CGeometry::Render(_device);
            
        }

    protected:
        std::shared_ptr< CVertexBuffer<TVertexType > > m_VertexBuffer;
    };

    template < typename TVertexType >
    class CTemplatedIndexedGeometry : public CGeometry
    {
    public:
        CTemplatedIndexedGeometry(CVertexBuffer< TVertexType >* aVertexBuffer, CIndexBuffer * aIndexBuffer)
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

        virtual void RenderIndexed(uint32 IndexCount = -1, uint32 StartIndexLocation = 0, uint32 BaseVertexLocation = 0)
        {
            CGeometry::Render(_device);
            
        }

    private:
        CIndexBuffer*  m_IndexBuffer;
        CVertexBuffer<TVertexType> * m_VertexBuffer;
    };
}