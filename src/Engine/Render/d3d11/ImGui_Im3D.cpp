#include "Render.h"

#include <imgui.h>
#include "ImGui_Im3D.h"

#include "Device.h"
#include "Vertex.h"
#include "Buffer.h"
#include "Shader.h"
#include "ShaderStage.h"

#include "Cameras/Camera.h"

#include "Engine.h"

extern bool        ImGui_ImplDX11_Init(void* hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);
extern void        ImGui_ImplDX11_Shutdown();
extern void        ImGui_ImplDX11_NewFrame();

namespace render
{
    namespace ImGui_Im3D
    {
        struct Layout
        {
            Float4x4 mViewProj;
            Float2 mViewport;
        };

        CConstantBuffer< Layout > mCBIm3d;
        CDynamicVertexBuffer< CIm3dVertex > mVBIm3d;

        std::shared_ptr<CShader> mPointsShader;
        std::shared_ptr<CShader> mLinesShader;
        std::shared_ptr<CShader> mTrianglesShader;

        void ShutDown()
        {
            ImGui_ImplDX11_Shutdown();
        }

        void Im3D_Draw(const Im3d::DrawList& _drawList)
        {
            Im3d::AppData& ad = Im3d::GetAppData();

            helios::CEngine& lEngine = helios::CEngine::GetInstance();
            CDevice& lDevice = lEngine.GetDevice();

            ID3D11Device* d3d = lDevice.Device();
            ID3D11DeviceContext* ctx = lDevice.ImmediateContext();

            // setting the framebuffer, viewport and pipeline states can (and should) be done prior to calling Im3d::Draw
            lDevice.ResetViewport();
            lDevice.SetBlendState(BlendState::Im3dBlend);
            lDevice.SetDepthStencilState(DepthStencilState::DepthDisabled);
            lDevice.SetRasterizerState(RasterizerState::NoCull);

            mCBIm3d.Data.mViewport = ad.m_viewportSize;
            mCBIm3d.Data.mViewProj = lEngine.GetMainCamera()->GetViewProjection();

            mCBIm3d.Apply(ctx);
            mVBIm3d.Apply(d3d, ctx, (CIm3dVertex*)_drawList.m_vertexData, _drawList.m_vertexCount);

            mCBIm3d.BindVS(ctx, 0);

            // select shader/primitive topo
            switch (_drawList.m_primType)
            {
            case Im3d::DrawPrimitive_Points:
                ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
                mPointsShader->Bind(ctx);
                mCBIm3d.BindGS(ctx, 0);
                mVBIm3d.Bind(ctx);
                ctx->Draw(_drawList.m_vertexCount, 0);
                mPointsShader->Unbind(ctx);
                break;
            case Im3d::DrawPrimitive_Lines:
                ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
                mLinesShader->Bind(ctx);
                mCBIm3d.BindGS(ctx, 0);
                mVBIm3d.Bind(ctx);
                ctx->Draw(_drawList.m_vertexCount, 0);
                mLinesShader->Unbind(ctx);
                break;
            case Im3d::DrawPrimitive_Triangles:
                ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                mTrianglesShader->Bind(ctx);
                mVBIm3d.Bind(ctx);
                ctx->Draw(_drawList.m_vertexCount, 0);
                mTrianglesShader->Unbind(ctx);
                break;
            default:
                HELIOSASSERT(false);
                return;
            };
        }

        // At the top of each frame, the application must fill the Im3d::AppData struct and then call Im3d::NewFrame().
        // The example below shows how to do this, in particular how to generate the 'cursor ray' from a mouse position
        // which is necessary for interacting with gizmos.
        void Update(float dt)
        {
            helios::CEngine& lEngine = helios::CEngine::GetInstance();
            render::CWindow& lWindow = lEngine.GetWindow();

            AppData& ad = GetAppData();

            graphics::CCameraPtr lMainCamera = lEngine.GetMainCamera();
            const Float4x4& lProjection = lMainCamera->GetProjection();
            const Float4x4& lWorld = lMainCamera->GetWorld();

            ad.m_deltaTime = dt;
            ad.m_viewportSize = Float2((float)lWindow.GetWidth(), (float)lWindow.GetHeight());
            ad.m_viewOrigin = lMainCamera->GetPosition(); // for VR use the head position
            ad.m_worldUp = Vec3(0.0f, 1.0f, 0.0f); // used internally for generating orthonormal bases
            ad.m_projOrtho = lMainCamera->IsOrtho();

            // m_projScaleY controls how gizmos are scaled in world space to maintain a constant screen height 
            ad.m_projScaleY = ad.m_projOrtho
                ? 2.0f / lProjection(1, 1) // use far plane height for an ortho projection
                : tanf(Radians(lMainCamera->GetFovDeg())* 0.5f) * 2.0f // or vertical fov for a perspective projection
                ;

            // World space cursor ray from mouse position; for VR this might be the position/orientation of the HMD or a tracked controller.
            Float2 cursorPos = lWindow.GetWindowRelativeCursor();
            cursorPos = (cursorPos / ad.m_viewportSize) * 2.0f - 1.0f;
            cursorPos.y = -cursorPos.y; // window origin is top-left, ndc is bottom-left
            Float3 rayOrigin, rayDirection;
            if (ad.m_projOrtho)
            {
                rayOrigin.x = cursorPos.x / lProjection(0, 0);
                rayOrigin.y = cursorPos.y / lProjection(1, 1);
                rayOrigin.z = 0.0f;
                rayOrigin = lWorld * Float4(rayOrigin, 1.0f);
                rayDirection = lWorld * Float4(0.0f, 0.0f, -1.0f, 0.0f);

            }
            else {
                rayOrigin = ad.m_viewOrigin;
                rayDirection.x = cursorPos.x / lProjection(0, 0);
                rayDirection.y = cursorPos.y / lProjection(1, 1);
                rayDirection.z = -1.0f;
                rayDirection = lWorld * Float4(Normalize(rayDirection), 0.0f);
            }
            ad.m_cursorRayOrigin = rayOrigin;
            ad.m_cursorRayDirection = rayDirection;

            // Fill the key state array; using GetAsyncKeyState here but this could equally well be done via the window proc.
            // All key states have an equivalent (and more descriptive) 'Action_' enum.
            ad.m_keyDown[Im3d::Mouse_Left/*Im3d::Action_Select*/] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;

            // The following key states control which gizmo to use for the generic Gizmo() function. Here using the left ctrl
            // key as an additional predicate.
            bool ctrlDown = (GetAsyncKeyState(VK_LCONTROL) & 0x8000) != 0;
            ad.m_keyDown[Im3d::Key_L/*Action_GizmoLocal*/] = ctrlDown && (GetAsyncKeyState(0x4c) & 0x8000) != 0;
            ad.m_keyDown[Im3d::Key_T/*Action_GizmoTranslation*/] = ctrlDown && (GetAsyncKeyState(0x54) & 0x8000) != 0;
            ad.m_keyDown[Im3d::Key_R/*Action_GizmoRotation*/] = ctrlDown && (GetAsyncKeyState(0x52) & 0x8000) != 0;
            ad.m_keyDown[Im3d::Key_S/*Action_GizmoScale*/] = ctrlDown && (GetAsyncKeyState(0x53) & 0x8000) != 0;

            // Enable gizmo snapping by setting the translation/rotation/scale increments to be > 0
            ad.m_snapTranslation = ctrlDown ? 0.1f : 0.0f;
            ad.m_snapRotation = ctrlDown ? Im3d::Radians(15.0f) : 0.0f;
            ad.m_snapScale = ctrlDown ? 0.5f : 0.0f;
        }

        void NewFrame()
        {
            Im3d::NewFrame();
            ImGui_ImplDX11_NewFrame();
        }

        void Render()
        {
            Im3d::Draw();
            ImGui::Render();
        }

        void Initialize()
        {
            helios::CEngine& lEngine = helios::CEngine::GetInstance();
            CDevice& lDevice = lEngine.GetDevice();

            ID3D11Device* d3d = lDevice.Device();
            ID3D11DeviceContext* ctx = lDevice.ImmediateContext();

            mCBIm3d.Initialize(d3d);

            mPointsShader = lEngine.GetAssetManager().Get<CShader>("im3d_points_shader");
            mLinesShader = lEngine.GetAssetManager().Get<CShader>("im3d_lines_shader");
            mTrianglesShader = lEngine.GetAssetManager().Get<CShader>("im3d_triangles_shader");


            Im3d::GetAppData().drawCallback = &Im3D_Draw;

            // Setup ImGui binding
            ImGui_ImplDX11_Init(lEngine.GetWindow().winId(), d3d, ctx);

            ImGuiIO& io = ImGui::GetIO();
            io.Fonts->AddFontFromFileTTF("fonts/Roboto-Regular.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

        }
    }
}