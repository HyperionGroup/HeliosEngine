#pragma once
#include "Core.h"
#include <Singleton.h>
#include "Assets/AssetManager.h"

namespace helios
{
    class CEngine : public core::CSingleton< CEngine >
    {
    public:
        CEngine(){}
        virtual ~CEngine() {}
        const io::CAssetManager& GetAssetManager() const { return mAssetManager;  }
        io::CAssetManager& GetAssetManager() { return mAssetManager; }

    protected:
        io::CAssetManager mAssetManager;
    };
}