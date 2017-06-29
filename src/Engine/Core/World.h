#pragma once

#include <anax\anax.hpp>

#include <Singleton.h>
#include "GameObject.h"

namespace core
{
    class CWorld : public CSingleton<CWorld>
    {
    public:
        CWorld() = default;
        virtual ~CWorld() = default;
        CGameObject NewGameObject();
        template< typename T > void AddSystem(T& _system)
        {
            mAnaxWorld.addSystem(_system);
        }
        void Update();
    private:
        anax::World mAnaxWorld;
    };
}