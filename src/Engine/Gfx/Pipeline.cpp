#include "Pipeline.h"

#include <bgfx/bgfx.h>
#include <bx/fpumath.h>

#include "RenderableWorld.h"

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

    namespace pipeline
    {
        void ClearView(uint8_t _id, uint16_t _flags, float r, float g, float b, float a , float _depth, uint8_t _stencil)
        {
            bgfx::setViewClear(_id
                , _flags
                , GetUint32Argb(r,g, b, a)
                , _depth
                , _stencil
            );
        }

        void SetViewProjection()
        {
            float at[3] = { 0.0f, 0.0f,   0.0f };
            float eye[3] = { 0.0f, 0.0f, -35.0f };

            // Set view and projection matrix for view 0.
            const bgfx::HMD* hmd = bgfx::getHMD();
            if (NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING))
            {
                float view[16];
                bx::mtxQuatTranslationHMD(view, hmd->eye[0].rotation, eye);
                bgfx::setViewTransform(0, view, hmd->eye[0].projection, BGFX_VIEW_STEREO, hmd->eye[1].projection);

                // Set view 0 default viewport.
                //
                // Use HMD's width/height since HMD's internal frame buffer size
                // might be much larger than window size.
                bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
            }
            else
            {
                float view[16];
                bx::mtxLookAt(view, eye, at);

                float proj[16];
                bx::mtxProj(proj, 60.0f, float(1280) / float(720), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
                bgfx::setViewTransform(0, view, proj);

                // Set view 0 default viewport.
                bgfx::setViewRect(0, 0, 0, uint16_t(1280), uint16_t(720));
            }
        }

        void EndRender()
        {
            // Advance to next frame. Rendering thread will be kicked to
            // process submitted rendering primitives.
            bgfx::frame();
        }

        void BeginRender()
        {
            // This dummy draw call is here to make sure that view 0 is cleared
            // if no other draw calls are submitted to view 0.
            bgfx::touch(0);
        }

        void RenderWorldLayer(const char* _layer)
        {
            CRenderableWorld::GetInstance().Render(_layer);
        }

        void RenderDebugText(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format)
        {
            bgfx::dbgTextPrintf(_x, _y, _attr, _format);
        }

    }
}