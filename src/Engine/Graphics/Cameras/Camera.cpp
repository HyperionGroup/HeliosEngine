#include "Graphics.h"

#include "Camera.h"

namespace graphics
{
    void CCamera::CalculateMatrices()
    {
        mWorld = LookAt( mPosition, mPosition - mForward );
        mView = Inverse(mWorld);

        float lFovRad = Radians(mFovDeg);
        float n = 0.1f;
        float f = 500.0f;
        float a = (float)800 / (float)600;
        float scale = tanf(lFovRad * 0.5f) * n;

        if (mOrtho) {
            n = -500.0f;
            scale = 5.0f;
            float r = scale * a;
            float l = -scale * a;
            float t = scale;
            float b = -scale;
            mProjection = Float4x4(
                2.0f / (r - l), 0.0f, 0.0f, -(r + l) / (r - l),
                0.0f, 2.0f / (t - b), 0.0f, -(t + b) / (t - b),
                0.0f, 0.0f, -2.0f / (f - n), -(f + n) / (f - n),
                0.0f, 0.0f, 0.0f, 1.0f
            );
        }
        else {
            float r = a * scale;
            float l = -r;
            float t = scale;
            float b = -t;
            mProjection = Float4x4(
                2.0f * n / (r - l), 0.0f, (r + l) / (r - l), 0.0f,
                0.0f, 2.0f * n / (t - b), (t + b) / (t - b), 0.0f,
                0.0f, 0.0f, -1.0f, -2.0f * n,
                0.0f, 0.0f, -1.0f, 0.0f
            );
        }
        mViewProjection = mProjection * mView;
    }
}
