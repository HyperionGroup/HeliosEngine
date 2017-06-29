#pragma once
#include "Core/Core.h"

#include "Serialization/Serializable.h"
#include "Assets/AssetManager.h"
#include "ImmediateGui/ImmediateGui.h"

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

    protected:
        io::CSerializableEntityConstructor mSerializableConstructor;
        io::CAssetManager                  mAssetManager;

        bool mInitialized;

    protected:
        void RegisterSerializableEntities();
        void RegisterGameAssets();
    };
}