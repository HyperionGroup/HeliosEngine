#include "Engine.h"

#include "Shaders/Shader.h"
#include "Shaders/ShaderStages/VertexStage.h"
#include "Shaders/ShaderStages/PixelStage.h"
#include "Shaders/ShaderStages/GeometryStage.h"
#include "Geometry/Vertex.h"

#include "Cameras/Camera.h"

#include "ImGui_Im3D.h"

namespace helios
{
    void CEngine::Initialize()
    {
        if (mWindow.Create())
        {
#if defined(HELIOSPLATFORM_WIN)
            // force the current working directory to the exe location
            TCHAR buf[MAX_PATH] = {};
            DWORD buflen;
            winAssert(buflen = GetModuleFileName(0, buf, MAX_PATH));
            char* pathend = strrchr(buf, (int)'\\');
            *(++pathend) = '\0';
            std::string strbuff = buf;
            strbuff.erase(strbuff.find("HeliosEngine\\") + 12);
            strbuff += "\\data\\";
            winAssert(SetCurrentDirectory(strbuff.c_str()));
            fprintf(stdout, "Set current directory: '%s'\n", buf);
#endif
            mDevice.Initialize(mWindow.winID());

            RegisterSerializableEntities();
            RegisterGameAssets();

            render::ImGui_Im3D::Initialize();

            // Set up the main camera
            mCamera = std::make_shared< graphics::CCamera >();
            mCamera->SetIsOrtho(false);
            mCamera->SetPosition(Float3(0.0f, 2.0f, 3.0f));
            mCamera->SetForward(Normalize(Float3(0.0f, -0.5f, -1.0f)));
            mCamera->SetFovDeg(50.0f);

            mInitialized = true;
        }
    }

    void CEngine::Run()
    {
        HELIOSASSERT(mInitialized);

        float lBackColor[4] = { 1.0f, 0.25f ,0.25f , 0.25f };

        Im3d::Context& ctx = Im3d::GetContext();
        Im3d::AppData& ad = Im3d::GetAppData();

        while (mWindow.Update())
        {
            mDevice.ImmediateContext()->ClearRenderTargetView(mDevice.BackBuffer(), lBackColor);
            Im3d::Draw();
            //ImGui::Render();
            mDevice.Present();
        }
    }

    void CEngine::ShutDown()
    {
        render::ImGui_Im3D::ShutDown();
        mWindow.ShutDown();
    }

    void CEngine::RegisterSerializableEntities()
    {
        // Render library entities
        mSerializableConstructor.Register<render::CShader>("shader");
        mSerializableConstructor.Register<render::CVertexStage<render::CIm3dVertex> >("vs_im3d");
        mSerializableConstructor.Register<render::CVertexStage<render::CMeshVertex> >("vs_mesh");
        mSerializableConstructor.Register<render::CVertexStage<render::CScreenVertex> >("vs_screen");
        mSerializableConstructor.Register<render::CVertexStage<render::CAnimatedVertex> >("vs_animated");
        mSerializableConstructor.Register<render::CPixelStage>("ps");
        mSerializableConstructor.Register<render::CGeometryStage>("gs");
        //
    }

    void CEngine::RegisterGameAssets()
    {
        // Register game Assets classes here!
        mAssetManager.Register<render::CShader>("shaders", "shaders/shaders.hcf");
        //
    }
}