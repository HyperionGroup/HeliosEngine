#pragma once

#include "Serialization\Serializable.h"
#include "Bindings\Bindeable.h"
#include "Name.h"
#include "Render.h"

namespace render
{
    class CGeometry;
    class CModel : public io::CSerializableEntity, public core::CName, public io::CBindeableEntity
    {
        SERIALIZABLE
        BINDEABLE
    public:
        CModel() = default;
        virtual ~CModel() = default;

    protected:
        std::string mFilename;
        std::vector< CGeometry* > mGeometries;
    };
}