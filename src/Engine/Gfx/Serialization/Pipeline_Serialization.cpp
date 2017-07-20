#include "Gfx.h"

#include "Pipeline.h"

#include "Serialization/Serialization.h"

namespace gfx
{
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
      LOG_INFO_APPLICATION(lInputNode["type"].GetString());
      lTask->Deserialize(lInputNode);
      Add(lTask->GetName().c_str(), lTask);
    }
  }
}