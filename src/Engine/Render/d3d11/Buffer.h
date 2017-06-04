#pragma once

namespace render
{
    class CBuffer
    {
    public:
        CBuffer()
            : mBuffer(nullptr)
            , mInitialized(false)
            , mUsage(D3D11_USAGE_DEFAULT)
        {}
        virtual ~CBuffer() {}
        virtual void ShutDown()
        {
            HELIOSASSERT(mInitialized);
            if( mInitialized )
            {
                if (mBuffer)
                {
                    mBuffer->Release();
                    mBuffer = nullptr;
                }
                mInitialized = false;
            }
        }
        virtual void Bind(ID3D11DeviceContextPtr _device) = 0;
        ID3D11BufferPtr Buffer() const { return mBuffer; }

        bool IsInitizalized() const { return mInitialized; }
    protected:
        D3D11_USAGE mUsage;
        ID3D11BufferPtr mBuffer;
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
            mUsage = D3D11_USAGE_DYNAMIC;
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

        void Initialize(ID3D11DevicePtr _device, const TVertexType * _data, uint32 _numVertices)
        {
            HELIOSASSERT(!mInitialized);
            HELIOSASSERT(_data);

            D3D11_BUFFER_DESC lVB;
            ZeroMemory(&lVB, sizeof(lVB));
            lVB.Usage = mUsage;
            lVB.ByteWidth = sizeof(TVertexType)*_numVertices;
            lVB.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            lVB.CPUAccessFlags = 0;

            D3D11_SUBRESOURCE_DATA lSubresourceData;
            ZeroMemory(&lSubresourceData, sizeof(lSubresourceData));
            lSubresourceData.pSysMem = _data;

            DXCall(_device->CreateBuffer(&lVB, &lSubresourceData, &mBuffer));

            mInitialized = true;
            mNumVertexs = _numVertices;
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

        virtual void Bind(ID3D11DeviceContextPtr _device)
        {
            HELIOSASSERT(mInitialized);
            _device->IASetIndexBuffer(mBuffer, DXGI_FORMAT_R32_UINT, 0);
        }

        void Initialize(ID3D11DevicePtr _device, const uint32* _indices, uint32 _numIndices)
        {
            D3D11_BUFFER_DESC lIB;
            ZeroMemory(&lIB, sizeof(lIB));
            lIB.Usage = mUsage;
            lIB.ByteWidth = sizeof(uint32) * _numIndices;
            lIB.BindFlags = D3D11_BIND_INDEX_BUFFER;
            lIB.CPUAccessFlags = 0;

            D3D11_SUBRESOURCE_DATA lSubresourceData;
            ZeroMemory(&lSubresourceData, sizeof(lSubresourceData));
            lSubresourceData.pSysMem = _indices;

            DXCall(_device->CreateBuffer(&lIB, &lSubresourceData, &mBuffer));

            mInitialized = true;
            mNumIndices = _numIndices;
        }

        inline uint32 GetIndexCount() const { return mNumIndices; }
        inline void SetIndexCount(uint32 _numIndices) { mNumIndices = _numIndices; }

    protected:
        uint32 mNumIndices;
    };

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

        void Apply(ID3D11DeviceContextPtr _device, const TVertexType * _data)
        {
            HELIOSASSERT(mInitialized);
            D3D11_MAPPED_SUBRESOURCE mappedResource;
            DXCall(_device->Map(mBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));
            CopyMemory(mappedResource.pData, &_data, sizeof(TVertexType)*mNumVertexs);
            _device->Unmap(mBuffer, 0);
        }
    };
}