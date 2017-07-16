#include "Gfx.h"

#include "Pipeline.h"
#include "imgui/imgui.h"

namespace gfx
{
    CRenderPipeline::CRenderPipeline()
    {
      Register<CBeginFrame>();
      Register<CEndFrame>();
      Register<CRenderDebugText>();
      Register<CClear>();
    }

    void CRenderPipeline::Execute()
    {
      for (auto& lTask : mArray)
        lTask->Execute();
    }
}