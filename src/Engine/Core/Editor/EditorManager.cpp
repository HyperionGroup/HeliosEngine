#include "Core.h"
#include "Editable.h"
#include "EditorManager.h"

#include <bx/uint32_t.h>
#include "common.h"
#include "bgfx_utils.h"
#include "entry/input.h"
#include "imgui/imgui.h"
#include "Logic/Script.h"
#include "Gfx\Window.h"

namespace editor
{
  void CEditorManager::Update()
  {
    gfx::CWindow& lWindow = gfx::CWindow::GetInstance();
    const entry::MouseState& lMouseState = lWindow.GetMouseState();
    const uint8_t* chars = inputGetChar();
    if (chars)
    {
      imguiBeginFrame(lMouseState.m_mx
        , lMouseState.m_my
        , (lMouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
        | (lMouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
        | (lMouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
        , lMouseState.m_mz
        , uint16_t(lWindow.GetWidth())
        , uint16_t(lWindow.GetHeight())
        , *chars
      );
    }
    else
    {
      imguiBeginFrame(lMouseState.m_mx
        , lMouseState.m_my
        , (lMouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
        | (lMouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
        | (lMouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
        , lMouseState.m_mz
        , uint16_t(lWindow.GetWidth())
        , uint16_t(lWindow.GetHeight())
      );
    }

    if (ImGui::BeginDock("Hierarchy"))
    {
    }
    ImGui::EndDock();

    if (ImGui::BeginDock("Helios"))
    {
    }

    ImGui::EndDock();

    if (ImGui::BeginDock("Inspector"))
    {
      if (mCurrentObject)
        mCurrentObject->OnEditor();
    }
    ImGui::EndDock();

    imguiEndFrame();
  }
}
