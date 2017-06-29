#include "Gfx.h"

#include "Systems.h"

namespace gfx
{
    void OpaqueLayerRenderSystem::render()
    {
        auto entities = getEntities();
        for (auto& entity : entities)
        {
            // Apply transform
            // Apply material
            // Apply mesh
        }
    }

    void InitSystems()
    {

    }
}