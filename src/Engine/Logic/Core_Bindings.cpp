#include "Logic.h"

#include "Core/Logger\Logger.h"
#include "Core/Containers.h"

#include <sol.hpp>
#include "Core/Name.h"

namespace logic
{
    void bind_name(sol::state& _state)
    {
        _state.new_simple_usertype<core::CName>("coreName",
            "SetName", &core::CName::SetName,
            "GetName", &core::CName::GetName
            );
    }

    void bind_core_lib(sol::state& _state)
    {
        bind_name(_state);
    }
}