#pragma once

namespace graphcs
{
    class CCamera
    {
    public:
        CCamera() = default;
        virtual ~CCamera() = default;
    private:
        // 3d camera
        bool  m_camOrtho;
        Float3  m_camPos;
        Float3  m_camDir;
        float m_camFovDeg;
        float m_camFovRad;
        Float4x4  m_camWorld;
        Float4x4  m_camView;
        Float4x4  m_camProj;
        Float4x4  m_camViewProj;

        void Initialize();
        void ShutDown();
    };
}