#include "Gfx.h"

#include "Pipeline.h"

#include "Core/Serialization/Serialization.h"

#include <imgui/imgui.h>
#include <imgui_internal.h>

namespace gfx
{
  void CRenderTask::OnEditor()
  {
    ImGui::Separator();
    // conversion
    static char buff[32];
    char *buffer = new char[mName.size() + 128];
    std::strcpy(buffer, mName.c_str());
    static int i = 0;
    bool result = ImGui::InputText(std::string("Name").c_str(), buff, 32);
    if (result)
      mName = std::string(buffer);
    delete[] buffer;
  }

  void CBeginFrame::OnEditor()
  {
    CRenderTask::OnEditor();
  }

  void CEndFrame::OnEditor()
  {
    CRenderTask::OnEditor();
  }

  void CRenderDebugText::OnEditor()
  {
    CRenderTask::OnEditor();
  }

  void CClear::OnEditor()
  {
    CRenderTask::OnEditor();
    ImGui::Checkbox("Clear Color", &mClearColor);
    ImGui::ColorEdit4("Color", &mColor.r, false);
    mColorEncoded = mColor.GetUint32Argb();
    ImGui::Checkbox("Clear Stencil", &mClearStencil);
    ImGui::Checkbox("Clear Depth", &mClearDepth);
    ImGui::SameLine();
    ImGui::DragFloat("Depth Clear Value", &mDepthValue, 0.0f, 1.0f);
  }

}