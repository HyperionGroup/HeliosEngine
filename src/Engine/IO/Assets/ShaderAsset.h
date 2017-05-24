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
    class CShaderAsset : public CAsset , std::enable_shared_from_this<CShaderAsset>
    {
    public:
    private:
        struct StageDesc
        {
            std::string type;
            std::string file;
            std::string macros;
        };

        std::string mVertexType;
        std::vector< StageDesc > mStagesDescriptors;
        render::CShader *mShader;
    public:
        CShaderAsset() = default;
        virtual ~CShaderAsset() = default;
        render::CShader* GetShader() const { return mShader; }
        virtual bool Load();
        virtual bool Unload();
    };
}
#endif