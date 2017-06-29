#include "Engine.h"
#include "Core/Core.h"

#include "Gfx/Shader.h"
#include "Gfx/Shader.h"
#include "Gfx/Vertex.h"

#include "Gfx/Material.h"

namespace helios
{
    void CEngine::Initialize()
    {
        /*        if (mWindow.Create(600,800))
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
            mDevice.Initialize(mWindow);

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

            render::CQuad lQuad;
        }*/
    }

    void CEngine::Run()
    {
        /*
        HELIOSASSERT(mInitialized);

        float lBackColor[4] = { 1.0f, 0.25f ,0.25f , 0.25f };

        Im3d::Context& ctx = Im3d::GetContext();
        Im3d::AppData& ad = Im3d::GetAppData();

        bool show_test_window = true;

        while (mWindow.Update())
        {
            render::ImGui_Im3D::NewFrame();
            render::ImGui_Im3D::Update(0.0f);
            OnGui();
            mDevice.ImmediateContext()->ClearRenderTargetView(mDevice.BackBuffer(), lBackColor);
            render::ImGui_Im3D::Render();
            mDevice.Present();
        }*/
    }

    void CEngine::OnGui()
    {
        /*
        BeginWindow("Project", Float2(0, 0));
        mAssetManager.OnGui();
        EndWindow();
        */
    }

    void CEngine::ShutDown()
    {
        //render::ImGui_Im3D::ShutDown();
        //mWindow.ShutDown();
    }

    void CEngine::RegisterSerializableEntities()
    {
        /*
        // Render library entities
        mSerializableConstructor.Register<render::CShader>("shader");
        mSerializableConstructor.Register<render::CVertexStage<render::CIm3dVertex> >("vs_im3d");
        mSerializableConstructor.Register<render::CVertexStage<render::CMeshVertex> >("vs_mesh");
        mSerializableConstructor.Register<render::CVertexStage<render::CScreenVertex> >("vs_screen");
        mSerializableConstructor.Register<render::CVertexStage<render::CAnimatedVertex> >("vs_animated");
        mSerializableConstructor.Register<render::CPixelStage>("ps");
        mSerializableConstructor.Register<render::CGeometryStage>("gs");
        mSerializableConstructor.Register<render::CModel>("model");
        //

        // Graphics library entities
        mSerializableConstructor.Register<graphics::CMaterial>("material");
        mSerializableConstructor.Register<graphics::CTemplatedMaterialParameter<float>>("float_parameter");
        mSerializableConstructor.Register<graphics::CTemplatedMaterialParameter<Float2>>("float2_parameter");
        mSerializableConstructor.Register<graphics::CTemplatedMaterialParameter<Float3>>("float3_parameter");
        mSerializableConstructor.Register<graphics::CTemplatedMaterialParameter<Float4>>("float4_parameter");
        mSerializableConstructor.Register<graphics::CTemplatedMaterialParameter<CColor>>("color_parameter");
        //
        */
    }

    void CEngine::RegisterGameAssets()
    {
        /*
        // Register game Assets classes here!
        mAssetManager.Register<render::CShader>("shaders", "shaders/shaders.hcf");
        mAssetManager.Register<render::CModel>("models", "models/models.hcf");
        //
        */
    }
}