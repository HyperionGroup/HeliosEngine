#include "IO.h"

#include "Assets/AssetManager.h"
#include "Assets/asset.h"
#include "Assets/TextureAsset.h"
#include "Assets/ShaderAsset.h"

namespace io
{
    CAssetManager::CAssetManager()
    {
        // Register game Assets classes here!
        Register<io::CShaderAsset>();
        Register<io::CTextureAsset>();
        //
    }

    CAssetManager::~CAssetManager()
    {
#ifdef _DEBUG
        // Only in debug show the alive Assets that have not been released correctly
        DumpAliveAssets();
#endif
        m_AssetHolders.clear();
    }

    void CAssetManager::DumpAliveAssets() const
    {
        for (auto& AssetTypeHolder : m_AssetHolders)
        {
            if (AssetTypeHolder.second->GetTotalBytesSize())
            {
                LOG_WARNING_APPLICATION("-----------");
                LOG_WARNING_APPLICATION("[CAssetManager::DumpAliveAssets][%s]", AssetTypeHolder.first.c_str());
                AssetTypeHolder.second->DumpAliveAssets();
                LOG_WARNING_APPLICATION("-----------");
            }
        }
    }

    void CAssetManager::AssetTypeHolder::DumpAliveAssets() const
    {
        for (auto& Asset : m_Assets)
        {
            CAsset* res = Asset.second;
            //LOG_WARNING_APPLICATION("[%s][%d references][%d bytes]", res->GetFilename().c_str(), res->GetRefCount(), res->GetBytesSize());
        }
    }

    void CAssetManager::AssetTypeHolder::AddAsset(const std::string& name, CAsset* Asset)
    {
        HELIOSASSERT(Asset && !name.empty());

        //m_TotalBytesSize += Asset->GetBytesSize();
        m_Assets[name] = Asset;
    }

    CAsset* CAssetManager::AssetTypeHolder::GetAsset(const std::string& name) const
    {
        HELIOSASSERT(!name.empty());

        CAsset* Asset = nullptr;
        std::map< const std::string, CAsset* >::const_iterator find = m_Assets.find(name);
        if (find != m_Assets.end())
        {
            Asset = find->second;
            //Asset->IncRefCount();
        }
        return Asset;
    }

    void CAssetManager::AssetTypeHolder::ReleaseAsset(const std::string& name)
    {
        HELIOSASSERT(!name.empty());

        std::map< const std::string, CAsset* >::const_iterator find = m_Assets.find(name);
        if (find != m_Assets.end())
        {
            CAsset* Asset = find->second;
            //Asset->DecRefCount();

            // If the number of references reach 0, this will mean that the Asset is not needed
            // anymore, therefore the total storage must be updated and the Asset unloaded and deleted
            /*if (Asset->GetRefCount() == 0)
            {
                //m_TotalBytesSize -= Asset->GetBytesSize();
                Asset->Unload();
                m_Assets.erase(find);
                CHECKED_DELETE(Asset);
            }*/
        }
        else
        {
            LOG_WARNING_APPLICATION("Unable to release Asset %s", name.c_str());
        }
    }
}
