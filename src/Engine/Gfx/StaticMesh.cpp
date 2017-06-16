#include "Gfx.h"
#include "StaticMesh.h"

#include "Vertex.h"

namespace
{
    static gfx::CPositionColorVertex s_cubeVertices[] =
    {
        { Float3(-1.0f,  1.0f,  1.0f), 0xff000000 },
        { Float3(1.0f,  1.0f,  1.0f), 0xff0000ff },
        { Float3(-1.0f, -1.0f,  1.0f), 0xff00ff00 },
        { Float3(1.0f, -1.0f,  1.0f), 0xff00ffff },
        { Float3(-1.0f,  1.0f, -1.0f), 0xffff0000 },
        { Float3(1.0f,  1.0f, -1.0f), 0xffff00ff },
        { Float3(-1.0f, -1.0f, -1.0f), 0xffffff00 },
        { Float3(1.0f, -1.0f, -1.0f), 0xffffffff },
    };

    static const uint16_t s_cubeTriList[] =
    {
        0, 1, 2, // 0
        1, 3, 2,
        4, 6, 5, // 2
        5, 6, 7,
        0, 2, 4, // 4
        4, 2, 6,
        1, 5, 3, // 6
        5, 7, 3,
        0, 4, 1, // 8
        4, 5, 1,
        2, 3, 6, // 10
        6, 3, 7,
    };

    static const uint16_t s_cubeTriStrip[] =
    {
        0, 1, 2,
        3,
        7,
        1,
        5,
        0,
        4,
        2,
        6,
        7,
        4,
        5,
    };
}

namespace gfx
{
    CCubePrimitive::CCubePrimitive()
    {
        BX_UNUSED(s_cubeTriList, s_cubeTriStrip);
        mVB.Initialize(s_cubeVertices, 8);
        mIB.Initialize(s_cubeTriStrip, ARRAYSIZE(s_cubeTriStrip));
    }

    CStaticMesh::~CStaticMesh()
    {
        mIB.ShutDown();
        mVB.ShutDown();
    }

    void CStaticMesh::Render()
    {
        mVB.Bind();
        mIB.Bind();
    }
}