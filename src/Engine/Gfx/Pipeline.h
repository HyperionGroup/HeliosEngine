#pragma once
#include "Gfx.h"

namespace gfx
{
    namespace pipeline
    {
        void BeginRender();
        void RenderWorldLayer( const char* _layer );
        void RenderDebugText(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format);
        void EndRender();
        void ClearView(uint8_t _id, uint16_t _flags, float r, float g, float b, float a, float _depth, uint8_t _stencil);
        void SetViewProjection();
    }
}