#include "Gfx.h"

#include "Pipeline.h"

#include "Serialization/Serialization.h"

namespace gfx
{
  void CRenderTask::Serialize(serialization::OutputArchive& _archive)
  {
    CName::Serialize(_archive);
    CEnabled::Serialize(_archive);
  }

  void CBeginFrame::Serialize(serialization::OutputArchive& _archive)
  {
    _archive.Begin<CBeginFrame>();
    CRenderTask::Serialize(_archive);
    _archive.End();
  }

  void CClear::Serialize(serialization::OutputArchive& _archive)
  {
    _archive.Begin<CClear>();
    CRenderTask::Serialize(_archive);
    _archive.Add("color", mClearColor, true);
    _archive.Add("depth", mClearDepth, true);
    _archive.Add("stencil", mClearStencil, false);
    _archive.Add("rgba", mColor, CColor(0,0,0,0) );
    _archive.End();
  }

  void CEndFrame::Serialize(serialization::OutputArchive& _archive)
  {
    _archive.Begin<CEndFrame>();
    CRenderTask::Serialize(_archive);
    _archive.End();
  }

  void CRenderDebugText::Serialize(serialization::OutputArchive& _archive)
  {
    _archive.Begin<CRenderDebugText>();
    CRenderTask::Serialize(_archive);
    _archive.Add("text", mText);
    _archive.Add("x", mX, 0u);
    _archive.Add("y", mY, 0u);
    _archive.End();
  }

  void CRenderTask::Deserialize(serialization::InputArchiveNode& _node)
  {
    CName::Deserialize(_node);
    CEnabled::Deserialize(_node);
  }

  void CRenderDebugText::Deserialize(serialization::InputArchiveNode& _node)
  {
    CRenderTask::Deserialize(_node);
    mText = serialization::Get<core::CStr>(_node, "text");
    mX = serialization::Get(_node, "x", 0u);
    mY = serialization::Get(_node, "y", 0u);
    LOG_INFO_APPLICATION("gfx::CRenderDebugText");
  }

  void CBeginFrame::Deserialize(serialization::InputArchiveNode& _node)
  {
    CRenderTask::Deserialize(_node);
  }

  void CEndFrame::Deserialize(serialization::InputArchiveNode& _node)
  {
    CRenderTask::Deserialize(_node);
  }

  void CClear::Deserialize(serialization::InputArchiveNode& _node)
  {
    CRenderTask::Deserialize(_node);
    mColor = serialization::Get<CColor>(_node, "rgba", CColor());
    mColorEncoded = mColor.GetUint32Argb();
  }
}