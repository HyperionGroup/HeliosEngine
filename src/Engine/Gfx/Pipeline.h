#pragma once
#include "Gfx.h"

#include "Core/Name.h"
#include "Core/Enabled.h"

namespace gfx
{
    struct CRenderTask : public core::CName, public core::CEnabled
    {
        virtual void Execute() = 0;
    };

    struct CBeginFrame : public CRenderTask
    {
        virtual void Execute();
    };

    struct CRenderDebugText : public CRenderTask
    {
        virtual void Execute();
        core::CStr mText;
        uint32_t mX;
        uint32_t mY;
    };
    
    struct CEndFrame : public CRenderTask
    {
        virtual void Execute();
    };

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