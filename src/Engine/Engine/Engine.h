#pragma once
#include "Core.h"
#include "Render.h"
#include "Graphics.h"

#include <Singleton.h>

#include "Serialization/Serializable.h"
#include "Assets/AssetManager.h"
#include "ImmediateGui/ImmediateGui.h"
#include "Window.h"
#include "d3d11/Device.h"

namespace helios
{
    class CEngine : public core::CSingleton< CEngine >, public gui::CImmediateGui
    {
    public:
        CEngine() = default;
        virtual ~CEngine() = default;

        void Initialize();
        void ShutDown();
        void Run();

        virtual void OnGui();

        const io::CSerializableEntityConstructor& GetSerializableEntityConstructor() const { return mSerializableConstructor;  }
        io::CSerializableEntityConstructor& GetSerializableEntityConstructor() { return mSerializableConstructor; }

        const io::CAssetManager& GetAssetManager() const { return mAssetManager; }
        io::CAssetManager& GetAssetManager() { return mAssetManager; }

        const render::CWindow& GetWindow() const { return mWindow; }
        render::CWindow& GetWindow() { return mWindow; }

        const render::CDevice& GetDevice() const { return mDevice; }
        render::CDevice& GetDevice() { return mDevice; }

        graphics::CCameraPtr GetMainCamera() const { return mCamera; }

    protected:
        io::CSerializableEntityConstructor mSerializableConstructor;
        io::CAssetManager                  mAssetManager;
        render::CWindow                    mWindow;
        render::CDevice                    mDevice;

        graphics::CCameraPtr               mCamera;

        bool mInitialized;

    protected:
        void RegisterSerializableEntities();
        void RegisterGameAssets();
    };
}