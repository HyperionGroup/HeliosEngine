#pragma once
#include "Core.h"
#include "Render.h"
#include <Singleton.h>

#include "Serialization/Serializable.h"
#include "Assets/AssetManager.h"
#include "Window.h"
#include "d3d11/Device.h"

namespace helios
{
    class CEngine : public core::CSingleton< CEngine >
    {
    public:
        CEngine() = default;
        virtual ~CEngine() = default;

        void Initialize();
        void ShutDown();
        void Run();

        const io::CSerializableEntityConstructor& GetSerializableEntityConstructor() const { return mSerializableConstructor;  }
        io::CSerializableEntityConstructor& GetSerializableEntityConstructor() { return mSerializableConstructor; }

        const io::CAssetManager& GetAssetManager() const { return mAssetManager; }
        io::CAssetManager& GetAssetManager() { return mAssetManager; }

        const user::CWindow& GetWindow() const { return mWindow; }
        user::CWindow& GetWindow() { return mWindow; }

        const render::CDevice& GetDevice() const { return mDevice; }
        render::CDevice& GetDevice() { return mDevice; }

    protected:
        io::CSerializableEntityConstructor mSerializableConstructor;
        io::CAssetManager                  mAssetManager;
        user::CWindow                      mWindow;
        render::CDevice                    mDevice;

        bool mInitialized;

    protected:
        void RegisterSerializableEntities();
        void RegisterGameAssets();
    };
}