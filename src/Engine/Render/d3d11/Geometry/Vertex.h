#pragma once

namespace render
{
    class CMeshVertex
    {
    public:
        Float3 position;
        Float3 normal;
        Float4 tangent;
        Float4 binormal;
        Float2 uv;
        Float2 uv2;
        CMeshVertex() = default;
        virtual ~CMeshVertex() = default;
        static void CreateInputLayout(ID3D11Device* _device, ID3DBlob *_vsBlob, ID3D11InputLayout **_inputLayout)
        {
            D3D11_INPUT_ELEMENT_DESC lDesc[] =
            {
                { "SV_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,      0, (UINT)offsetof(CMeshVertex, position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,      0, (UINT)offsetof(CMeshVertex, normal),   D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "TANGENT",     0, DXGI_FORMAT_R32G32B32A32_FLOAT,   0, (UINT)offsetof(CMeshVertex, tangent),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "BINORMAL",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,   0, (UINT)offsetof(CMeshVertex, binormal), D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,         0, (UINT)offsetof(CMeshVertex, uv),       D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "TEXCOORD",    1, DXGI_FORMAT_R32G32_FLOAT,         0, (UINT)offsetof(CMeshVertex, uv2),      D3D11_INPUT_PER_VERTEX_DATA, 0 },
            };
            DXCall(_device->CreateInputLayout(lDesc, ARRAYSIZE(lDesc), _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout));
        }
        static const uint32 Flags = Position | Normal | Tangent | Binormal | Uv;
    };

    class CScreenVertex
    {
    public:
        Float3 position;
        Float2 uv;
        CScreenVertex() = default;
        virtual ~CScreenVertex() = default;
    };

    class CAnimatedVertex
    {
    public:
        Float3 position;
        Float3 normal;
        Float4 tangent;
        Float4 binormal;
        Float2 uv;
        Float4 weight;
        Float4 indices;
        CAnimatedVertex() = default;
        virtual ~CAnimatedVertex() = default;
    };
}