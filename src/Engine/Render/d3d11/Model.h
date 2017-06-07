#pragma once

#include "Serialization\Serializable.h"
#include "ImmediateGui\ImmediateGui.h"
#include "Name.h"
#include "Render.h"

namespace render
{
    class CGeometry;
    class CModel : public io::CSerializableEntity, public core::CName, public gui::CImmediateGui
    {
        SERIALIZABLE
    public:
        CModel() = default;
        virtual ~CModel() = default;
        virtual void OnGui();

    protected:
        std::string mFilename;
        std::vector< CGeometry* > mGeometries;
    };
}