#pragma once
#include "Core.h"
#include "Render.h"
#include "Graphics.h"

#include <Singleton.h>

#include "Serialization/Serializable.h"
#include "Assets/AssetManager.h"
#include "Window/Window.h"
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

        const CWindow& GetWindow() const { return mWindow; }
        CWindow& GetWindow() { return mWindow; }

        const render::CDevice& GetDevice() const { return mDevice; }
        render::CDevice& GetDevice() { return mDevice; }

    protected:
        io::CSerializableEntityConstructor mSerializableConstructor;
        io::CAssetManager                  mAssetManager;
        CWindow                            mWindow;
        render::CDevice                    mDevice;

        graphics::CCameraPtr               mCamera;

        bool mInitialized;

    protected:
        void RegisterSerializableEntities();
        void RegisterGameAssets();
    };
}