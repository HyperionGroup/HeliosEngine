#include "Gfx.h"

#include "Material.h"
#include "Shader.h"

namespace gfx
{
    CMaterial::CMaterial()
        : CName("")
        , mShader( std::make_shared<CShader>() )
    {
        mShader->Initialize("vs_cubes", "fs_cubes");
    }

    void CMaterial::Render()
    {
        mShader->Bind();
    }
}
