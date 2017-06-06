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
                { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,         0, (UINT)offsetof(CMeshVertex, position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
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

    class CIm3dVertex
    {
    public:
        Float4 m_positionSize; // xyz = position, w = size
        CColor m_color;        // rgba8 (MSB = r)
        CIm3dVertex() = default;
        virtual ~CIm3dVertex() = default;
        static void CreateInputLayout(ID3D11Device* _device, ID3DBlob *_vsBlob, ID3D11InputLayout **_inputLayout)
        {
            D3D11_INPUT_ELEMENT_DESC lDesc[] =
            {
                { "POSITION_SIZE", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,   0, (UINT)offsetof(CIm3dVertex, m_positionSize), D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "COLOR",         0, DXGI_FORMAT_R8G8B8A8_UNORM,       0, (UINT)offsetof(CIm3dVertex, m_color),        D3D11_INPUT_PER_VERTEX_DATA, 0 },
            };
            DXCall(_device->CreateInputLayout(lDesc, ARRAYSIZE(lDesc), _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout));
        }
        static const uint32 Flags = Position4 | Color;
    };

    class CScreenVertex
    {
    public:
        Float3 position;
        Float2 uv;
        uint32 color;
        CScreenVertex() = default;
        virtual ~CScreenVertex() = default;
        static void CreateInputLayout(ID3D11Device* _device, ID3DBlob *_vsBlob, ID3D11InputLayout **_inputLayout)
        {
            D3D11_INPUT_ELEMENT_DESC lDesc[] = {
                { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,   0, (UINT)offsetof(CScreenVertex, position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,   0, (UINT)offsetof(CScreenVertex, uv),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, (UINT)offsetof(CScreenVertex, color), D3D11_INPUT_PER_VERTEX_DATA, 0 },
            };
            DXCall(_device->CreateInputLayout(lDesc, ARRAYSIZE(lDesc), _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout));
        }
        static const uint32 Flags = Position4 | Color;
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
        static void CreateInputLayout(ID3D11Device* _device, ID3DBlob *_vsBlob, ID3D11InputLayout **_inputLayout)
        {
            HELIOSASSERT(false);
            D3D11_INPUT_ELEMENT_DESC lDesc[] =
            {
                { "POSITION_SIZE", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,   0, (UINT)offsetof(CIm3dVertex, m_positionSize), D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "COLOR",         0, DXGI_FORMAT_R8G8B8A8_UNORM,       0, (UINT)offsetof(CIm3dVertex, m_color),        D3D11_INPUT_PER_VERTEX_DATA, 0 },
            };
            DXCall(_device->CreateInputLayout(lDesc, ARRAYSIZE(lDesc), _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout));
        }
        static const uint32 Flags = Position4 | Color;
    };
}