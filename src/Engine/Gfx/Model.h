#pragma once

#include "Core\Name.h"

namespace gfx
{
    class CGeometry;
    class CModel : public core::CName
    {
    public:
        CModel() = default;
        virtual ~CModel() = default;
        void Load(const core::CStr& _filename);

    protected:
        std::string mFilename;
        std::vector< CGeometry* > mGeometries;
    };
}