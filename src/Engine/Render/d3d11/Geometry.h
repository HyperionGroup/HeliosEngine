#pragma once
#include "Render.h"

namespace render
{
    class CGeometry
    {
    public:
        CGeometry(D3D11_PRIMITIVE_TOPOLOGY _topology) : mTopology(_topology) {}
        virtual ~CGeometry() {}

        virtual void Render(ID3D11DeviceContextPtr _device)
        {
            // Configure the type of topology to be renderer ( p.e. Triangles, Quads, points,... )
            _device->IASetPrimitiveTopology(mTopology);
        }

        virtual void RenderIndexed(ID3D11DeviceContextPtr _device, uint32 _indexCount = -1, uint32 _startIndexLocation = 0, uint32 _baseVertexLocation = 0)
        {
            // Configure the type of topology to be renderer ( p.e. Triangles, Quads, points,... )
            _device->IASetPrimitiveTopology(mTopology);
            HELIOSUNUSED(_indexCount);
            HELIOSUNUSED(_startIndexLocation);
            HELIOSUNUSED(_baseVertexLocation);
        }

    protected:
        D3D_PRIMITIVE_TOPOLOGY mTopology;
    };

    template< class TVertexType >
    class CTemplatedGeometry : public CGeometry
    {
    public:
        CTemplatedGeometry(CVertexBuffer<TVertexType>* VertexBuffer, D3D11_PRIMITIVE_TOPOLOGY _topology )
            : CGeometry(_topology)
            , m_VertexBuffer(VertexBuffer)
        {
        }

        virtual ~CTemplatedGeometry()
        {
            delete m_VertexBuffer;
        }

        virtual void Render(ID3D11DeviceContextPtr _device)
        {
            CGeometry::Render(_device);
            m_VertexBuffer->Bind(_device);
            _device->Draw(m_VertexBuffer->GetNumVertexs(), 0);
        }

    protected:
        CVertexBuffer<TVertexType> *m_VertexBuffer;
    };

    template < typename TVertexType >
    class CTemplatedIndexedGeometry : public CGeometry
    {
    public:
        CTemplatedIndexedGeometry(CVertexBuffer< TVertexType >* aVertexBuffer, CIndexBuffer * aIndexBuffer, D3D11_PRIMITIVE_TOPOLOGY _topology )
            : CGeometry(_topology)
            , m_VertexBuffer(aVertexBuffer)
            , m_IndexBuffer(aIndexBuffer)
        {
        }

        virtual ~CTemplatedIndexedGeometry()
        {
            delete m_VertexBuffer;
            delete m_IndexBuffer;
        }

        virtual void RenderIndexed(ID3D11DeviceContextPtr _device, uint32 IndexCount = -1, uint32 StartIndexLocation = 0, uint32 BaseVertexLocation = 0)
        {
            CGeometry::Render(_device);
            m_VertexBuffer->Bind(_device);
            m_IndexBuffer->Bind(_device);
            _device->DrawIndexed(m_IndexBuffer->GetIndexCount(), StartIndexLocation, BaseVertexLocation);
        }

    private:
        CIndexBuffer*  m_IndexBuffer;
        CVertexBuffer<TVertexType> * m_VertexBuffer;
    };
}