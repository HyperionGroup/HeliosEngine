#pragma once

#include "Core.h"
#include "common.h"
#include "bgfx_utils.h"

namespace gfx
{
    struct CPositionColorVertex
    {
        static void init()
        {
            mDeclaration
                .begin()
                .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
                .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
                .end();
        };

        Float3 position;
        uint32 abgr;

        static bgfx::VertexDecl mDeclaration;
    };
}