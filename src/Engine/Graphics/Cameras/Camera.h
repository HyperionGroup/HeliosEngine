#pragma once

namespace graphics
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

        void SetPosition(const Float3& _position) { mPosition = _position;  }
        const Float3& GetPosition() const { return mPosition; }
        void SetForward(const Float3& _forward) { mForward = _forward; }
        const Float3& GetForward() const { return mForward; }

        const Float4x4& GetWorld() const { return mWorld; }
        const Float4x4& GetView() const { return mView; }
        const Float4x4& GetProjection() const { return mProjection; }
        const Float4x4& GetViewProjection() const { return mViewProjection; }

        void CalculateMatrices();

    protected:
        bool    mOrtho;
        float   mFovDeg;

        Float3  mPosition;
        Float3  mForward;

        Float4x4  mWorld;
        Float4x4  mView;
        Float4x4  mProjection;
        Float4x4  mViewProjection;
    };
}