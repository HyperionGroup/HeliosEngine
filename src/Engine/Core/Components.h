#pragma once
#include <anax/Component.hpp>

namespace core
{
    struct TransformComponent : anax::Component
    {
        float mtx[16];
        void SetPosition(const Float3& _position);
    };
}