#pragma once

#include "Core/Entities/Components.h"

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