#pragma once
#include <anax/Component.hpp>
#include "Mathematics.h"

namespace core
{
  struct TransformComponent : anax::Component
  {
    core::CStr id;
    Float3 position;
    Quaternion rotation;
    Float3 scale;
    float mtx[16];
    void SetPosition(const Float3& _position);
  };
}