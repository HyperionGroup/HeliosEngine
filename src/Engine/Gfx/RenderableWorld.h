#pragma once

#include "Core/Name.h"
#include "Core/Containers.h"

namespace gfx
{
    class CStaticMesh;
    class CMaterial;
    class CRenderableObject : public core::CName
    {
    public:
        CRenderableObject() = default;
        virtual ~CRenderableObject() = default;
        virtual void Render() = 0;
        void SetPosition(Float3 _position);
    public:
        float mtx[16];
    };

    class CRenderableMesh : public CRenderableObject
    {
    public:
        CRenderableMesh() = default;
        virtual ~CRenderableMesh() = default;
        virtual void Render();
    protected:
        std::shared_ptr< CMaterial > mMaterial;
        std::shared_ptr< CStaticMesh > mMesh;
    };

    class CRenderablePrimitive: public CRenderableMesh
    {
    public:
        CRenderablePrimitive();
        virtual ~CRenderablePrimitive() = default;
    };

    class CLayer : public core::CName, public core::CStringArrayMap< CRenderableObject >
    {
    public:
        CLayer() = default;
        virtual ~CLayer() = default;
        void Render();
    };

    class CScene : public core::CName, public core::CStringArrayMap< CLayer >
    {
    public:
        CScene() = default;
        virtual ~CScene() = default;
        void Render(const char* _layer);
    };

    class CRenderableWorld : public core::CSingleton< CRenderableWorld >, public core::CStringArrayMap< CScene >
    {
    public:
        CRenderableWorld() = default;
        virtual ~CRenderableWorld() = default;
        void Render(const char* _layer);
    };
}