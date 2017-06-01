#pragma once

#include "StringUtils.h"
#include "Containers.h"
#include "Serialization/Serializable.h"

namespace io
{
    class CAssetTypeHolder
    {
    public:
        CAssetTypeHolder() = default;
        virtual ~CAssetTypeHolder() = default;
    };

    template< typename T >
    class CAssetTypeHolderT : public CAssetTypeHolder, public core::CStringArrayMap<T>
    {
    public:
        CAssetTypeHolderT() = default;
        CAssetTypeHolderT(const std::string& _tag, const std::string& _heliosConfigFilename)
            : CAssetTypeHolder()
            , mHeliosConfigFilename(_heliosConfigFilename)
        {
            if (!_heliosConfigFilename.empty())
            {
                const io::CSerializableEntityConstructor& lEntityCntr = helios::CEngine::GetInstance().GetSerializableEntityConstructor();
                io::CSerializableDocument lDocument = io::utils::OpenDocument(_heliosConfigFilename);
                const io::CSerializableNode& lShaders = lDocument[_tag.c_str()];
                HELIOSASSERT(lShaders.IsArray());
                for (const io::CSerializableNode& m : lShaders.GetArray())
                {
                    std::shared_ptr< io::CSerializableEntity > lEntity = lEntityCntr.Create(m["type"].GetString());
                    lEntity->Deserialize(m);
                    std::shared_ptr< T > lEntityChildClass = std::static_pointer_cast<T>(lEntity);
                    Add(lEntityChildClass->GetName(), lEntityChildClass );
                }
            }
        }
        virtual ~CAssetTypeHolderT() = default;

    protected:
        std::string mHeliosConfigFilename;
    };
}