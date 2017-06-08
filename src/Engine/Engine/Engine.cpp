#include "Engine.h"

#include "Shaders/Shader.h"
#include "Shaders/ShaderStages/VertexStage.h"
#include "Shaders/ShaderStages/PixelStage.h"
#include "Shaders/ShaderStages/GeometryStage.h"
#include "Vertex.h"

#include "Model\Model.h"
#include "Im3DDraw.h"

#include "Materials\Material.h"
#include "Materials\MaterialParameter.h"

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

            render::Im3d_Draw::Initialize();

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
        render::Im3d_Draw::ShutDown();
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
    }

    void CEngine::RegisterGameAssets()
    {
        // Register game Assets classes here!
        mAssetManager.Register<render::CShader>("shaders", "shaders/shaders.hcf");
        mAssetManager.Register<render::CModel>("models", "models/models.hcf");
        //
    }
}