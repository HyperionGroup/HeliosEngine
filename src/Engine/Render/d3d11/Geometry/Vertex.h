#ifndef _VERTEX_HH_
#define _VERTEX_HH_

#pragma once

namespace render
{
    class CVertex
    {
    public:
        template<typename... Args>
        CVertex(Args&&... args)
            : mDesc(new D3D11_INPUT_ELEMENT_DESC[sizeof...(args)])
            , mFlags(0)
            , mNumElements(sizeof...(args))
        {
            std::vector<VertexFlags> lFlags = { args... };
            ZeroMemory(mDesc, sizeof(D3D11_INPUT_ELEMENT_DESC) * mNumElements);
            uint32 lOffset = 0;
            for (uint32 i = 0; i < mNumElements; ++i)
            {
                const VertexFlags lFlag = lFlags[i];
                D3D11_INPUT_ELEMENT_DESC& lDesc = mDesc[i];
                lDesc.AlignedByteOffset = lOffset;
                switch (lFlag)
                {
                case render::Position:
                {
                    lDesc.SemanticName = "SV_POSITION";
                    lDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
                    lOffset += sizeof(float) * 3;
                    break;
                }
                case render::Position4:
                {
                    lDesc.SemanticName = "SV_POSITION";
                    lDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                    lOffset += sizeof(float) * 4;
                    break;
                }
                case render::Normal:
                {
                    lDesc.SemanticName = "NORMAL";
                    lDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
                    lOffset += sizeof(float) * 3;
                    break;
                }
                case render::Tangent:
                {
                    lDesc.SemanticName = "TANGENT";
                    lDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                    lOffset += sizeof(float) * 4;
                    break;
                }
                case render::Binormal:
                {
                    lDesc.SemanticName = "BINORMAL";
                    lDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                    lOffset += sizeof(float) * 4;
                    break;
                }
                case render::Uv:
                {
                    lDesc.SemanticName = "TEXCOORD";
                    lDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
                    lOffset += sizeof(float) * 2;
                    break;
                }
                case render::Uv2:
                {
                    lDesc.SemanticName = "TEXCOORD";
                    lDesc.SemanticIndex = 1;
                    lDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
                    lOffset += sizeof(float) * 2;
                    break;
                }
                case render::Weight:
                {
                    lDesc.SemanticName = "BLENDWEIGHT";
                    lDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                    lOffset += sizeof(float) * 4;
                    break;
                }
                case render::Indices:
                {
                    lDesc.SemanticName = "BLENDINDICES";
                    lDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                    lOffset += sizeof(float) * 4;
                    break;
                }
                default:
                    HELIOSASSERT(false);
                    break;
                }
                mFlags |= lFlag;
            }
        }
        virtual ~CVertex()
        {
            if( mDesc )
                delete[] mDesc;
            mDesc = nullptr;
        }
        void CreateInputLayout(ID3D11Device* _device, ID3DBlob *_vsBlob, ID3D11InputLayout **_inputLayout)
        {
            DXCall(_device->CreateInputLayout(mDesc, mNumElements, _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout));
        }
        const uint32 GetVertexFlags() const { return mFlags; }
    private:
        D3D11_INPUT_ELEMENT_DESC* mDesc;
        uint32 mFlags;
        uint32 mNumElements;
    };

    class CMeshVertex : public CVertex
    {
    public:
        Float3 position;
        Float3 normal;
        Float4 tangent;
        Float4 binormal;
        Float2 uv;
        CMeshVertex()
            : CVertex( render::Position,
                       render::Normal,
                       render::Tangent,
                       render::Binormal,
                       render::Uv ) {}
        virtual ~CMeshVertex() {}
    };

    class CScreenVertex : public CVertex
    {
    public:
        Float3 position;
        Float2 uv;
        CScreenVertex() : CVertex(render::Position, render::Uv ) {}
        virtual ~CScreenVertex() {}
    };

    class CAnimatedVertex : public CVertex
    {
    public:
        Float3 position;
        Float3 normal;
        Float4 tangent;
        Float4 binormal;
        Float2 uv;
        Float4 weight;
        Float4 indices;
        CAnimatedVertex() : CVertex(render::Position, render::Normal, render::Uv) {}
        virtual ~CAnimatedVertex() {}
    };
}

#endif
