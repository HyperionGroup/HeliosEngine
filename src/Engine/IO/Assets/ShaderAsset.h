#ifndef _ShaderAsset_
#define _ShaderAsset_

#pragma once

#include "Asset.h"

namespace io
{
    class CShaderAsset : public CAsset
    {
        SERIALIZABLE
    private:
        std::vector< std::string > mFlags;
        std::string mVertexStage;
        std::string mPixelStage;
    public:
        CShaderAsset();
        virtual ~CShaderAsset();
        virtual bool Load();
    };
}
#endif