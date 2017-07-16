#include "Gfx.h"

#include "Gfx/Camera.h"
#include "common.h"
#include "bgfx_utils.h"

namespace gfx
{
    void CCamera::BindMatrices(uint32_t _width, uint32_t _height)
    {
        // Set view and projection matrix for view 0.
        const bgfx::HMD* hmd = bgfx::getHMD();
        if (NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING))
        {
            float view[16];
            bx::mtxQuatTranslationHMD(view, hmd->eye[0].rotation, &mEye.x);
            bgfx::setViewTransform(0, view, hmd->eye[0].projection, BGFX_VIEW_STEREO, hmd->eye[1].projection);

            // Set view 0 default viewport.
            //
            // Use HMD's width/height since HMD's internal frame buffer size
            // might be much larger than window size.
            bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
        }
        else
        {
            //bx::mtxLookAt(mView.data(), &mEye.x, &mAt.x);
            //bx::mtxProj(mProjection.data(), 60.0f, float(_width) / float(_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
            //bgfx::setViewTransform(0, mView., mProjection.data() );

            // Set view 0 default viewport.
            bgfx::setViewRect(0, 0, 0, uint16_t(_width), uint16_t(_height));
        }
    }
}
