#pragma once

#include "AssetTypeHolder.h"

namespace io
{
    class CAsset;
    class CAssetManager
    {
        NON_COPYABLE_CLASS(CAssetManager);

    public:
        template <typename T>
        void Register( const std::string& _heliosConfigFilename )
        {
            static_assert(std::is_base_of<CAsset, T>::value, "Registered type must derive from Asset");
            m_AssetHolders[typeid(T).name()] = std::make_shared< CAssetTypeHolderT<T> >(_heliosConfigFilename);
        }

        template<typename T>
        std::shared_ptr< T > GetAsset(const std::string& _name)
        {
            HELIOSASSERT(!_name.empty() && m_AssetHolders.find(typeid(T).name()) != m_AssetHolders.end());
            std::shared_ptr<CAssetTypeHolderT<T>> lHolder = std::static_pointer_cast<CAssetTypeHolderT<T>>(m_AssetHolders[typeid(T).name()]);
            return lHolder->GetAsset(_name);
        }

        template< typename T >
        void ReleaseAsset(const std::string& name)
        {
            HELIOSASSERT(!name.empty() && m_AssetHolders.find(typeid(T).name()) != m_AssetHolders.end());

            m_AssetHolders[typeid(T).name()]->ReleaseAsset(name);
        }

        std::map <std::string, std::shared_ptr<CAssetTypeHolder> > m_AssetHolders;
        
        CAssetManager();
        virtual ~CAssetManager();

        void DumpAliveAssets() const;
    };
}