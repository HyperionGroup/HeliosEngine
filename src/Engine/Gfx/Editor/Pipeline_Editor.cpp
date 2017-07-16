#include "Gfx.h"

#include "Pipeline.h"

#include "Serialization.h"

#include <imgui/imgui.h>
#include <imgui_internal.h>

namespace gfx
{
  void CRenderPipeline::OnEditor()
  {
    if (ImGui::CollapsingHeader("Render Tasks"))
    {
      for (auto& lTask : mArray)
        lTask->OnEditor();
    }
  }
}