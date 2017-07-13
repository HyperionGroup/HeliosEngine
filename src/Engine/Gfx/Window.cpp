#include "Gfx.h"

#include "Window.h"

namespace gfx
{
    void CWindow::Init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height)
    {
      Args args(_argc, _argv);

      m_width = _width;
      m_height = _height;
      m_debug = BGFX_DEBUG_TEXT;
      m_reset = BGFX_RESET_VSYNC;

      bgfx::init(args.m_type, args.m_pciId);
      bgfx::reset(m_width, m_height, m_reset);

      // Enable debug text.
      bgfx::setDebug(m_debug);
    }

    bool CWindow::Update()
    {
      return entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState);
    }
}