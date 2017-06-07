#pragma once

#include "Serialization\Serializable.h"
#include "Name.h"

namespace render
{
    class CGeometry;
    class CQuad : public io::CSerializableEntity, public core::CName
    {
        SERIALIZABLE
    public:
        CQuad();
        virtual ~CQuad() = default;
    };
}