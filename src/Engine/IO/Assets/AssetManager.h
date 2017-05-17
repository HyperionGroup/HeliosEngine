/* Copyright (C) Ubisoft Entertainment - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#pragma once

#include <map>

namespace io
{
    class CAsset;
    class CAssetManager
    {
        NON_COPYABLE_CLASS(CAssetManager);

    private:
        class AssetTypeHolder
        {
        public:
            AssetTypeHolder() = default;
            virtual ~AssetTypeHolder() = default;

            CAsset* GetAsset(const std::string& name) const;
            void    AddAsset(const std::string& name, CAsset* Asset);
            void    ReleaseAsset(const std::string& name);

            uint32  GetTotalBytesSize() const { return m_TotalBytesSize; }

            void    DumpAliveAssets() const;

        protected:
            std::map< const std::string, CAsset* > m_Assets;
            uint32 m_TotalBytesSize;
        };

    public:
        template <typename T>
        void Register()
        {
            static_assert(std::is_base_of<CAsset, T>::value, "Registered type must derive from Asset");
            m_AssetHolders[typeid(T).name()] = std::make_shared<AssetTypeHolder>();
        }

        template<typename T>
        T* GetAsset(const std::string& name)
        {
            ASSERT(!name.empty() && m_AssetHolders.find(typeid(T).name()) != m_AssetHolders.end());

            shared_ptr<AssetTypeHolder>& holder = m_AssetHolders[typeid(T).name()];
            CAsset* Asset = holder->GetAsset(name);
            if (!Asset)
            {
                Asset = new Asset_TYPE();
                if (Asset->Load(name))
                {
                    holder->AddAsset(name, Asset);
                }
                else
                {
                    LOG_WARNING_APPLICATION("Unable to load Asset %s of type %s", name.c_str(), typeid(Asset_TYPE).name());
                    CHECKED_DELETE(Asset);
                }
            }

            return static_cast< Asset_TYPE* >(Asset);
        }

        template< typename T >
        void ReleaseAsset(const std::string& name)
        {
            ASSERT(!name.empty() && m_AssetHolders.find(typeid(T).name()) != m_AssetHolders.end());

            m_AssetHolders[typeid(T).name()]->ReleaseAsset(name);
        }

    private:
        friend class Engine;

        std::map <std::string, std::shared_ptr<AssetTypeHolder>> m_AssetHolders;
        
        CAssetManager();
        virtual ~CAssetManager();

        void DumpAliveAssets() const;
    };
}