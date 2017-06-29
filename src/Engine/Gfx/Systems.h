#pragma once

#include <anax/anax.hpp>

#include "Core/Components.h"
#include "Components.h"

namespace gfx
{
    struct OpaqueLayerRenderSystem : anax::System<anax::Requires<RenderableComponent, OpaqueLayerComponent, core::TransformComponent>>
    {
        void render();
        bool isValid() const { return true; }
    };

    void InitSystems();
}