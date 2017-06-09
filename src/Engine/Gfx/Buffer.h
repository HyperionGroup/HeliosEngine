#pragma once

#include "Gfx.h"

namespace render
{
    class CBuffer
    {
    public:
        CBuffer()
            : mInitialized(false)
        {}
        virtual ~CBuffer() {}
        virtual void ShutDown() 
        {
        }
        bool IsInitizalized() const { return mInitialized; }
    protected:
        bool mInitialized;
    };

    template<typename T>
    class CConstantBuffer : public CBuffer
    {
    public:
        T Data;
    public:
        CConstantBuffer()
            : CBuffer()
        {
        }
    };

    template< class TVertexType >
    class CVertexBuffer : public CBuffer
    {
    public:
        CVertexBuffer()
            : CBuffer()
        {
        }

        virtual ~CVertexBuffer()
        {
            mNumVertexs = 0u;
        }

        void Initialize(const TVertexType * _data, uint32 _numVertices)
        {
            HELIOSASSERT(!mInitialized);
            HELIOSASSERT(_data);

            m_vbh = bgfx::createVertexBuffer
            (
                // Static data can be passed with bgfx::makeRef
                bgfx::makeRef(_data, _numVertices * sizeof(TVertexType)) , TVertexType::mDeclaration
            );

            mInitialized = true;
            mNumVertexs = _numVertices;
        }

        virtual void ShutDown()
        {
            HELIOSASSERT(mInitialized);
            bgfx::destroyVertexBuffer(m_vbh);
        }

        void Bind()
        {
            bgfx::setVertexBuffer(0, m_vbh);
        }

        inline uint32 GetNumVertexs() const { return mNumVertexs; }
        inline void   SetNumVertexs(uint32 _numVertex) { mNumVertexs = _numVertex; }
        inline uint32 GetStride() const { return sizeof(TVertexType); }
    protected:
        bgfx::VertexBufferHandle m_vbh;
        uint32        mNumVertexs;
    };

    template < typename TIndexType >
    class CIndexBuffer : public CBuffer
    {
    public:
        CIndexBuffer()
            : CBuffer()
            , mNumIndices(0u)
        {
        }

        virtual ~CIndexBuffer()
        {
            mNumIndices = 0u;
        }

        void Initialize(const TIndexType* _indices, uint32 _numIndices)
        {
            HELIOSASSERT(!mInitialized);
            HELIOSASSERT(_indices);

            // Create static index buffer.
            m_ibh = bgfx::createIndexBuffer(
                // Static data can be passed with bgfx::makeRef
                bgfx::makeRef(s_cubeTriStrip, _numIndices * sizeof(TIndexType) )
            );

            mInitialized = true;
            mNumIndices = _numIndices;
        }

        void Bind()
        {
            bgfx::setIndexBuffer(m_ibh);
        }

        void ShutDown()
        {
            bgfx::destroyIndexBuffer(m_ibh);
        }

        inline uint32 GetIndexCount() const { return mNumIndices; }
        inline void SetIndexCount(uint32 _numIndices) { mNumIndices = _numIndices; }

    protected:
        uint32 mNumIndices;
        bgfx::IndexBufferHandle m_ibh;
    };

    template < typename TIndexType>
    class CDynamicIndexBuffer : public CIndexBuffer<TIndexType>
    {
    public:
        CDynamicIndexBuffer()
            : CIndexBuffer()
        {
        }

        virtual ~CDynamicIndexBuffer()
        {
        }

        void Apply(const uint32* _data, uint32 _numIndices)
        {
            HELIOSASSERT(mInitialized);

            if (mNumIndices != _numIndices)
            {
                ShutDown();
                Initialize(_data, mNumIndices);
            }
            else
            {
                //TODO
            }
        }
    };

    template< class TVertexType >
    class CDynamicVertexBuffer : public CVertexBuffer< TVertexType >
    {
    public:
        CDynamicVertexBuffer()
            : CVertexBuffer()
        {

        }

        virtual ~CDynamicVertexBuffer()
        {
        }

        void Apply(const TVertexType * _data, uint32 _numVertices)
        {
            HELIOSASSERT(mInitialized);

            if (mNumVertexs != _numVertices)
            {
                ShutDown();
                Initialize(_data, _numVertices);
            }
            else
            {
               
            }
        }
    };
}