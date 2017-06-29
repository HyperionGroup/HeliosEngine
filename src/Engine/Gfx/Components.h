#pragma once

#include "Core/Components.h"

namespace gfx
{
    struct RenderableComponent : anax::Component
    {
        CStaticMeshSptr mStaticMesh;
    };

    struct OpaqueLayerComponent : anax::Component
    {
    };

    struct TransparentLayerComponent : anax::Component
    {
    };
}