#include "Gfx.h"

#include "RenderTasks.h"

#include <bx/uint32_t.h>
#include "common.h"
#include "bgfx_utils.h"
#include <imgui/imgui.h>
#include <imgui_internal.h>

#include "Gfx/Window.h"

namespace gfx
{
    namespace 
    {
        inline uint8_t FloatToByte(float fValue)
        {
            int i = static_cast<int>(0xff * fValue);
            if (i < 0)
                i = 0;
            else if (i > 0xff)
                i = 0xff;
            return static_cast<uint8_t>(i);
        }

        inline uint32_t GetUint32Argb( float r, float g, float b, float a)
        {
            return  (uint32_t)(FloatToByte(r) << 24) + (FloatToByte(g) << 16) + (FloatToByte(b) << 8) + FloatToByte(a);
        }
    }

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

    void CBeginFrame::Execute()
    {
      gfx::CWindow& lWindow = gfx::CWindow::GetInstance();

      // Set view 0 default viewport.
      bgfx::setViewRect(0, 0, 0, uint16_t(lWindow.GetWidth()), uint16_t(lWindow.GetHeight()));

      // This dummy draw call is here to make sure that view 0 is cleared
      // if no other draw calls are submitted to view 0.
      bgfx::touch(0);

      bgfx::dbgTextClear();
    }

    void CEndFrame::OnEditor()
    {
      CRenderTask::OnEditor();
    }

    void CEndFrame::Execute()
    {
      // Advance to next frame. Rendering thread will be kicked to
      // process submitted rendering primitives.
      bgfx::frame();
    }

    void CRenderDebugText::OnEditor()
    {
      CRenderTask::OnEditor();
    }

    void CRenderDebugText::Execute()
    {
      bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");

      const bgfx::Stats* stats = bgfx::getStats();
      bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters."
        , stats->width
        , stats->height
        , stats->textWidth
        , stats->textHeight
      );
    }

    void CClear::OnEditor()
    {
      CRenderTask::OnEditor();
      ImGui::Checkbox("Clear Color", &mClearColor);
      ImGui::ColorEdit4("Color", &mColor.r, false );
      mColorEncoded = GetUint32Argb(mColor.r, mColor.g, mColor.b, mColor.a);
      ImGui::Checkbox("Clear Stencil", &mClearStencil);
      ImGui::Checkbox("Clear Depth", &mClearDepth);
      ImGui::SameLine();
      ImGui::DragFloat("Depth Clear Value", &mDepthValue, 0.0f, 1.0f );
    }

    void CClear::Execute()
    {
      bgfx::setViewClear(0
        , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
        , mColorEncoded//m0x303030ff
        , 1.0f
        , 0
      );
    }
}