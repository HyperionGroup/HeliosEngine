#pragma once

#include "Serialization\Serializable.h"
#include "Name.h"

namespace render
{
    class CTexture;
}

namespace graphics
{
    class CMaterial : public io::CSerializableEntity, public core::CName
    {
        SERIALIZABLE
    public:
        CMaterial() = default;
        virtual ~CMaterial() = default;
        void Apply();
        std::shared_ptr< render::CTexture> GetTexture(TextureMap _map) const { return mTextures[static_cast<int>(_map)]; }

        uint32 GetParametersCount() const { return static_cast<uint32>(mParameters.size());  }
        std::shared_ptr< CMaterialParameter > GetParameter( uint32 _idx ) const { return mParameters[_idx]; }

    private:
        std::vector< std::shared_ptr< render::CTexture> >   mTextures;
        std::vector< std::shared_ptr< CMaterialParameter > > mParameters;
    };
}