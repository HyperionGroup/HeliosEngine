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

    void CRenderPipeline::Serialize() const
    {
      serialization::OutputArchive lOutputArchive("pipeline.hcf");
      for (auto& lTask : mArray)
        lTask->Serialize(lOutputArchive);
    }

    void CRenderPipeline::Deserialize()
    {
      Clear();
      serialization::InputArchive lInputArchive("pipeline.hcf");
      for (serialization::InputArchiveNode& lInputNode : lInputArchive.GetArray())
      {
        std::shared_ptr< CRenderTask > lTask = Create(lInputNode["type"].GetString());
        lTask->Deserialize(lInputNode);
        Add(lTask->GetName().c_str(), lTask);
      }
    }

    void CRenderPipeline::Execute()
    {
      for (auto& lTask : mArray)
        lTask->Execute();
    }

    void CRenderPipeline::OnEditor()
    {
      if (ImGui::BeginDock("CRenderPipeline"))
      {
        for (auto& lTask : mArray)
          lTask->OnEditor();
      }
      ImGui::EndDock();
    }
}