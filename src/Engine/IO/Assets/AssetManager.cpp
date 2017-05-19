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
        Register<CShaderAsset>("shaders/shaders.hcf");
        Register<CTextureAsset>("");
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
        /*
        for (auto& AssetTypeHolder : m_AssetHolders)
        {
            if (AssetTypeHolder.second->GetTotalBytesSize())
            {
                LOG_WARNING_APPLICATION("-----------");
                LOG_WARNING_APPLICATION("[CAssetManager::DumpAliveAssets][%s]", AssetTypeHolder.first.c_str());
                AssetTypeHolder.second->DumpAliveAssets();
                LOG_WARNING_APPLICATION("-----------");
            }
        }*/
    }
}
