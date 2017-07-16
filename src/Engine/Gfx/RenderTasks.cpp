#include "Gfx.h"

#include "RenderTasks.h"

#include <bx/uint32_t.h>
#include "common.h"
#include "bgfx_utils.h"

#include "Gfx/Window.h"

namespace gfx
{
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

    void CEndFrame::Execute()
    {
      // Advance to next frame. Rendering thread will be kicked to
      // process submitted rendering primitives.
      bgfx::frame();
    }

    void CRenderDebugText::Execute()
    {
      bgfx::dbgTextPrintf(0, 1, 0x0f, "Cfsadfasdfasdfasdolor can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");

      const bgfx::Stats* stats = bgfx::getStats();
      bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters."
        , stats->width
        , stats->height
        , stats->textWidth
        , stats->textHeight
      );
    }

    void CClear::Execute()
    {
      LOG_INFO_APPLICATION("CClear %d", mColorEncoded);
      bgfx::setViewClear(0
        , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
        , mColorEncoded
        , 1.0f
        , 0
      );
    }
}