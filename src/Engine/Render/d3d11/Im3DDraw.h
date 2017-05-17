#pragma once

namespace Im3d
{
    struct DrawList;
}

namespace render
{
    namespace Im3d_Draw
    {
        void Initialize();
        void ShutDown();
        void Draw(const Im3d::DrawList& _drawList);
    }
}
