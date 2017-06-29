#include "Gfx.h"
#include "RenderableWorld.h"

#include "Vertex.h"
#include "StaticMesh.h"
#include "Material.h"

namespace gfx
{
    CRenderablePrimitive::CRenderablePrimitive()
    {
        mMesh = std::make_shared<CCubePrimitive>();
        mMaterial = std::make_shared<CMaterial>();
    }

    void CRenderableMesh::Render()
    {
        mMesh->Render();
        mMaterial->Render();
    }

    void CRenderableWorld::Render(const char* _layer )
    {
        std::shared_ptr<CScene> lLayer = Get(_layer);
        if (lLayer)
            lLayer->Render(_layer);
    }

    void CScene::Render(const char* _layer)
    {
        std::shared_ptr<CLayer> lLayer = Get(_layer);
        if (lLayer)
            lLayer->Render();
    }

    void CLayer::Render()
    {
        for (auto& renderObj : mArray)
            renderObj->Render();
    }

    void CRenderableObject::SetPosition(Float3 _position)
    {
        mtx[12] = _position.x;
        mtx[13] = _position.y;
        mtx[14] = _position.z;
    }

}