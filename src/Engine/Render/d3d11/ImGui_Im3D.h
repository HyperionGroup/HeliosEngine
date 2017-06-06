#pragma once

namespace Im3d
{
    struct DrawList;
}

namespace render
{
    namespace ImGui_Im3D
    {
        void Initialize();
        void Update( float dt );
        void ShutDown();
    }
}
