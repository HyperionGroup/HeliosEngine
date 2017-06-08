#pragma once

#include "AssetTypeHolder.h"

namespace io
{
    class CAsset;
    class CAssetManager : public gui::CImmediateGui
    {
    public:
        template <typename T>
        void Register(const std::string& _tag, const std::string& _heliosConfigFilename )
        {
            static_assert(std::is_base_of<CSerializableEntity, T>::value, "The given class does not derive from CSerializableEntity");
            static_assert(std::is_base_of<core::CName, T>::value, "The given class does not derive from CName");
            HELIOSASSERT(mAssets.find(typeid(T).name()) == mAssets.end());
            mAssets[typeid(T).name()] = std::make_shared< CAssetTypeHolderT<T> >(_tag, _heliosConfigFilename);
        }

        template<typename T> std::shared_ptr< T > Get(const std::string& _name)
        {
            HELIOSASSERT(!_name.empty() && mAssets.find(typeid(T).name()) != mAssets.end());
            std::shared_ptr<CAssetTypeHolderT<T>> lHolder = std::static_pointer_cast<CAssetTypeHolderT<T>>(mAssets[typeid(T).name()]);
            return lHolder->Get(_name);
        }

        virtual void OnGui()
        {
            for (auto& holder : mAssets)
                holder.second->OnGui();
        }

        std::map <std::string, std::shared_ptr<CAssetTypeHolder> > mAssets;
        
        CAssetManager() = default;
        virtual ~CAssetManager() = default;
    };
}