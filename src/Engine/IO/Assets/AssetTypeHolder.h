#pragma once

#include "StringUtils.h"
#include <vector>

namespace io
{
    class CAsset;
    class CAssetTypeHolder
    {
    public:
        CAssetTypeHolder() = default;
        virtual ~CAssetTypeHolder() = default;
    };

    template< typename T >
    class CAssetTypeHolderT : public CAssetTypeHolder
    {
    public:
        CAssetTypeHolderT() = default;
        CAssetTypeHolderT(const std::string& _heliosConfigFilename)
            : CAssetTypeHolder()
            , m_TotalBytesSize(0u)
            , mHeliosConfigFilename(_heliosConfigFilename)
        {
            if (!_heliosConfigFilename.empty())
            {
                std::ifstream ss(_heliosConfigFilename);
                cereal::JSONInputArchive iarchive(ss);
                iarchive(make_nvp(GetTag(_heliosConfigFilename).c_str(), mAssets));
                for (size_t i = 0, lCount = mAssets.size(); i < lCount; ++i)
                    mAssetsMap[mAssets[i]->GetName()] = i;
            }
        }
        virtual ~CAssetTypeHolderT() = default;

        std::shared_ptr< T > GetAsset(const std::string& name) const
        {
            HELIOSASSERT(!name.empty());

            std::shared_ptr< T > Asset = nullptr;
            std::map< const std::string, size_t >::const_iterator find = mAssetsMap.find(name);
            if (find != mAssetsMap.end())
                Asset = mAssets[find->second];
            return Asset;
        }

        void    AddAsset(const std::string& name, CAsset* Asset)
        {
            /*HELIOSASSERT(Asset && !name.empty());

            //m_TotalBytesSize += Asset->GetBytesSize();
            m_Assets[name] = Asset;*/
        }

        void    ReleaseAsset(const std::string& name)
        {
        }

        uint32  GetTotalBytesSize() const { return m_TotalBytesSize; }

        void    DumpAliveAssets() const
        {
            for (auto& Asset : m_Assets)
            {
                CAsset* res = Asset.second;
                //LOG_WARNING_APPLICATION("[%s][%d references][%d bytes]", res->GetFilename().c_str(), res->GetRefCount(), res->GetBytesSize());
            }
        }

    protected:
        std::vector< std::shared_ptr<T> > mAssets;
        std::map< const std::string, size_t > mAssetsMap;
        uint32 m_TotalBytesSize;
        std::string mHeliosConfigFilename;
    };
}