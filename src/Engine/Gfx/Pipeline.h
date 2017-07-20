#pragma once
#include "Gfx.h"

#include "RenderTasks.h"
#include "Core/Utils/Containers.h"
#include "Core/Utils/Objectfactory.h"

namespace gfx
{
    class CRenderPipeline : public core::CObjectFactory< CRenderTask >, public core::CStringArrayMap< CRenderTask >
    {
    public:
        CRenderPipeline();
        virtual ~CRenderPipeline() = default;
        void Execute();
        void OnEditor();
        void Serialize() const;
        void Deserialize();
    };
}