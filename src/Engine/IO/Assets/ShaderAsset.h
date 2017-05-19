#ifndef _ShaderAsset_
#define _ShaderAsset_

#pragma once

#include "Asset.h"
namespace render
{
    class CShader;
}

namespace io
{
    class CShaderAsset : public CAsset
    {
        SERIALIZABLE
    private:
        struct ShaderPreprocessor
        {
            std::string name;
            std::string definition;

            // This method lets cereal know which data members to serialize
            template<class Archive>
            void serialize(Archive & archive)
            {
                archive(make_nvp("name", name));
                archive(make_nvp("definition", definition));
            }
        };

        std::string mSource;
        std::string mPreprocessorVS;
        std::string mPreprocessorGS;
        std::string mPreprocessorPS;
        render::CShader *mShader;
    public:
        CShaderAsset() = default;
        virtual ~CShaderAsset() = default;
        virtual bool Load();
        virtual bool Unload();
    };


#pragma region Serialization
    SERIALIZABLE_SAVE_DECLARATION(CShaderAsset)
    {
        CAsset::save(ar);
        ar(make_nvp("src", mSource));
        ar(make_nvp("vs", mPreprocessorVS));
        ar(make_nvp("ps", mPreprocessorGS));
        ar(make_nvp("gs", mPreprocessorPS));
    }

    SERIALIZABLE_LOAD_DECLARATION(CShaderAsset)
    {
        CAsset::load(ar);
        ar(make_nvp("src", mSource));
        FROM_ARCHIVE_SAFE("vs", mPreprocessorVS);
        FROM_ARCHIVE_SAFE("ps", mPreprocessorGS);
        FROM_ARCHIVE_SAFE("gs", mPreprocessorPS);
        Load();
    }
#pragma endregion Serialization
}
#endif