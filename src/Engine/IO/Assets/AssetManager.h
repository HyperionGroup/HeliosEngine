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
        T* GetAsset(const std::string& name)
        {
            ASSERT(!name.empty() && m_AssetHolders.find(typeid(T).name()) != m_AssetHolders.end());

            shared_ptr<AssetTypeHolder>& holder = m_AssetHolders[typeid(T).name()];
            CAsset* Asset = holder->GetAsset(name);
            if (!Asset)
            {
                Asset = new T();
                if (Asset->Load(name))
                {
                    holder->AddAsset(name, Asset);
                }
                else
                {
                    LOG_WARNING_APPLICATION("Unable to load Asset %s of type %s", name.c_str(), typeid(T).name());
                    CHECKED_DELETE(Asset);
                }
            }

            return static_cast< T* >(Asset);
        }

        template< typename T >
        void ReleaseAsset(const std::string& name)
        {
            ASSERT(!name.empty() && m_AssetHolders.find(typeid(T).name()) != m_AssetHolders.end());

            m_AssetHolders[typeid(T).name()]->ReleaseAsset(name);
        }

        std::map <std::string, std::shared_ptr<CAssetTypeHolder> > m_AssetHolders;
        
        CAssetManager();
        virtual ~CAssetManager();

        void DumpAliveAssets() const;
    };
}