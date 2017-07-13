#pragma once

#include <bx/uint32_t.h>
#include "common.h"
#include "bgfx_utils.h"

#include "Core/Singleton.h"

namespace gfx
{
    class CWindow : public core::CSingleton< CWindow >
    {
    public:
      CWindow() = default;
      virtual ~CWindow() = default;
      void Init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height);

      bool Update();
      const entry::MouseState& GetMouseState() const { return m_mouseState; }
      const uint32_t GetWidth() const { return m_width; }
      const uint32_t GetHeight() const { return m_height; }
      const uint32_t GetDebug() const { return m_debug; }
      const uint32_t GetReset() const { return m_reset; }

    protected:
      entry::MouseState m_mouseState;
      uint32_t m_width;
      uint32_t m_height;
      uint32_t m_debug;
      uint32_t m_reset;
    };
}