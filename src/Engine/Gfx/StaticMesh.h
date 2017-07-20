#pragma once

#include "Core/Name.h"
#include "Core/Utils/Containers.h"

#include "Vertex.h"
#include "Buffer.h"

namespace gfx
{
    class CStaticMesh : public core::CName
    {
    public:
        CStaticMesh() = default;
        virtual ~CStaticMesh();
        virtual void Render();
    protected:
        render::CVertexBuffer< CPositionColorVertex > mVB;
        render::CIndexBuffer< uint16_t > mIB;
    };

    class CCubePrimitive : public CStaticMesh
    {
    public:
        CCubePrimitive();
        virtual ~CCubePrimitive() = default;
    };
}