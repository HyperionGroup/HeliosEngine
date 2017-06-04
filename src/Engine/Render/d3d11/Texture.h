#pragma once
#include "Serialization\Serializable.h"

namespace render
{
    class CTexture : public io::CSerializableEntity
    {
        SERIALIZABLE
        private:
            render::PixelDesc   mColorFormat;
            SamplerType         mSampler;
            std::string         mFilename;
            TextureType         mType;

            ID3D11ShaderResourceViewPtr mResourceView;
            Float2 mSize;
            bool Load();

        public:
            CTexture() = default;
            virtual ~CTexture() = default;
            
            void Bind(uint32 aStageId, ID3D11DeviceContextPtr aContext);
            ID3D11ShaderResourceViewPtr GetRawResource() { return mResourceView; }
    };
}