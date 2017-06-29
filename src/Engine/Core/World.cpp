#include "Core.h"
#include "World.h"

namespace core
{
    CGameObject CWorld::NewGameObject()
    {
        auto& lEntity = mAnaxWorld.createEntity();
        return lEntity;
    }

    void CWorld::Update()
    {
        mAnaxWorld.refresh();
    }
}