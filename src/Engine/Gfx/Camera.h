#pragma once

namespace gfx
{
    class CCamera
    {
    public:
        CCamera() = default;
        virtual ~CCamera() = default;

        void SetIsOrtho(bool _ortho) { mOrtho = _ortho; }
        bool IsOrtho() const { return mOrtho; }

        void SetFovDeg(float _fov) { mFovDeg = _fov; }
        float GetFovDeg() const { return mFovDeg; }

        void SetEye(const Float3& _Eye) { mEye = _Eye;  }
        const Float3& GetEye() const { return mEye; }
        void SetAt(const Float3& _At) { mAt = _At; }
        const Float3& GetAt() const { return mAt; }

        //const Float4x4& GetWorld() const { return mWorld; }
        //const Float4x4& GetView() const { return mView; }
        //const Float4x4& GetProjection() const { return mProjection; }
        //const Float4x4& GetViewProjection() const { return mViewProjection; }

        void BindMatrices(uint32_t _width, uint32_t _height);

    protected:
        bool    mOrtho;
        float   mFovDeg;

        Float3  mEye;
        Float3  mAt;

        //Float4x4  mWorld;
        //Float4x4  mView;
        //Float4x4  mProjection;
        //Float4x4  mViewProjection;
    };
}