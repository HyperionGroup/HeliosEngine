#include "Render.h"
#include "ImGui_Im3D.h"

#include "Device.h"
#include "Geometry/Vertex.h"
#include "Buffers/ConstantBuffer.h"
#include "Shaders/ShaderStages/VertexStage.h"
#include "Buffers/DynamicVertexBuffer.h"

#include "Cameras/Camera.h"

#include "Engine.h"

#include "Shaders/Shader.h"

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
        CConstantBuffer< Float4x4 > mCBImgui;
        CDynamicVertexBuffer< Im3d::VertexData > mVB;

        std::shared_ptr<CShader> mImGuiShader;
        std::shared_ptr<CShader> mPointsShader;
        std::shared_ptr<CShader> mLinesShader;
        std::shared_ptr<CShader> mTrianglesShader;



        /*
        void ImGui_Draw(ImGui::ImDrawData* _drawData)
        {
        ImGuiIO& io = ImGui::GetIO();
        ID3D11Device* d3d = g_Example->m_d3dDevice;
        ID3D11DeviceContext* ctx = g_Example->m_d3dDeviceCtx;

        // (re)alloc vertex/index buffers
        static int s_vertexBufferSize = 0;
        if (!g_ImGuiVertexBuffer || s_vertexBufferSize < _drawData->TotalVtxCount) {
        if (g_ImGuiVertexBuffer) {
        g_ImGuiVertexBuffer->Release();
        g_ImGuiVertexBuffer = nullptr;
        }
        s_vertexBufferSize = _drawData->TotalVtxCount;
        g_ImGuiVertexBuffer = CreateVertexBuffer(s_vertexBufferSize * sizeof(ImDrawVert), D3D11_USAGE_DYNAMIC);
        }
        static int s_indexBufferSize = 0;
        if (!g_ImGuiIndexBuffer || s_indexBufferSize < _drawData->TotalIdxCount) {
        if (g_ImGuiIndexBuffer) {
        g_ImGuiIndexBuffer->Release();
        g_ImGuiIndexBuffer = nullptr;
        }
        s_indexBufferSize = _drawData->TotalIdxCount;
        g_ImGuiIndexBuffer = CreateIndexBuffer(s_indexBufferSize * sizeof(ImDrawIdx), D3D11_USAGE_DYNAMIC);
        }

        // copy and convert all vertices into a single contiguous buffer
        ImDrawVert* vtxDst = (ImDrawVert*)MapBuffer(g_ImGuiVertexBuffer, D3D11_MAP_WRITE_DISCARD);
        ImDrawIdx* idxDst = (ImDrawIdx*)MapBuffer(g_ImGuiIndexBuffer, D3D11_MAP_WRITE_DISCARD);
        for (int i = 0; i < _drawData->CmdListsCount; ++i) {
        const ImDrawList* cmdList = _drawData->CmdLists[i];
        memcpy(vtxDst, cmdList->VtxBuffer.Data, cmdList->VtxBuffer.Size * sizeof(ImDrawVert));
        memcpy(idxDst, cmdList->IdxBuffer.Data, cmdList->IdxBuffer.Size * sizeof(ImDrawIdx));
        vtxDst += cmdList->VtxBuffer.Size;
        idxDst += cmdList->IdxBuffer.Size;
        }
        UnmapBuffer(g_ImGuiVertexBuffer);
        UnmapBuffer(g_ImGuiIndexBuffer);

        // update constant buffer
        *(Mat4*)MapBuffer(g_ImGuiConstantBuffer, D3D11_MAP_WRITE_DISCARD)
        = Mat4(
        2.0f / io.DisplaySize.x, 0.0f, 0.0f, -1.0f,
        0.0f, 2.0f / -io.DisplaySize.y, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 0.0f
        );
        UnmapBuffer(g_ImGuiConstantBuffer);

        // set state
        D3D11_VIEWPORT viewport = {};
        viewport.Width = ImGui::GetIO().DisplaySize.x;
        viewport.Height = ImGui::GetIO().DisplaySize.y;
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        viewport.TopLeftX = viewport.TopLeftY = 0.0f;
        ctx->RSSetViewports(1, &viewport);

        unsigned int stride = sizeof(ImDrawVert);
        unsigned int offset = 0;
        ctx->IASetInputLayout(g_ImGuiInputLayout);
        ctx->IASetVertexBuffers(0, 1, &g_ImGuiVertexBuffer, &stride, &offset);
        ctx->IASetIndexBuffer(g_ImGuiIndexBuffer, sizeof(ImDrawIdx) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, 0);
        ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        ctx->VSSetShader(g_ImGuiVertexShader, nullptr, 0);
        ctx->VSSetConstantBuffers(0, 1, &g_ImGuiConstantBuffer);
        ctx->PSSetShader(g_ImGuiPixelShader, nullptr, 0);
        ctx->PSSetSamplers(0, 1, &g_ImGuiFontSampler);

        ctx->OMSetBlendState(g_ImGuiBlendState, nullptr, 0xffffffff);
        ctx->OMSetDepthStencilState(g_ImGuiDepthStencilState, 0);
        ctx->RSSetState(g_ImGuiRasterizerState);

        int vtxOffset = 0;
        int idxOffset = 0;
        for (int i = 0; i < _drawData->CmdListsCount; ++i) {
        const ImDrawList* cmdList = _drawData->CmdLists[i];
        for (const ImDrawCmd* pcmd = cmdList->CmdBuffer.begin(); pcmd != cmdList->CmdBuffer.end(); ++pcmd) {
        if (pcmd->UserCallback) {
        pcmd->UserCallback(cmdList, pcmd);
        }
        else {
        const D3D11_RECT r = { (LONG)pcmd->ClipRect.x, (LONG)pcmd->ClipRect.y, (LONG)pcmd->ClipRect.z, (LONG)pcmd->ClipRect.w };
        ctx->PSSetShaderResources(0, 1, (ID3D11ShaderResourceView**)&pcmd->TextureId);
        ctx->RSSetScissorRects(1, &r);
        ctx->DrawIndexed(pcmd->ElemCount, idxOffset, vtxOffset);
        }
        idxOffset += pcmd->ElemCount;
        }
        vtxOffset += cmdList->VtxBuffer.Size;
        }
        }
        */

        void ShutDown()
        {

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

            // If is not the first execution, and the number of vertex has changed re-init the VB
            if (mVB.IsInitizalized() && mVB.GetNumVertexs() != _drawList.m_vertexCount)
                mVB.ShutDown();

            // If is the first execution or the VB has been shutdown init the VB
            if (!mVB.IsInitizalized())
            {
                mVB.SetNumVertexs(_drawList.m_vertexCount);
                mVB.Initialize(d3d, _drawList.m_vertexData);
            }
            else
            {
                // If the only thing that has changed is the VB data itself only update the VB
                mVB.Apply(ctx, _drawList.m_vertexData);
            }

            mCBIm3d.BindVS(ctx, 0);

            // select shader/primitive topo
            switch (_drawList.m_primType)
            {
            case Im3d::DrawPrimitive_Points:
                ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
                mPointsShader->Bind(ctx);
                mCBIm3d.BindGS(ctx, 0);
                mVB.Bind(ctx);
                ctx->Draw(_drawList.m_vertexCount, 0);
                mPointsShader->Unbind(ctx);
                break;
            case Im3d::DrawPrimitive_Lines:
                ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
                mLinesShader->Bind(ctx);
                mCBIm3d.BindGS(ctx, 0);
                mVB.Bind(ctx);
                ctx->Draw(_drawList.m_vertexCount, 0);
                mLinesShader->Unbind(ctx);
                break;
            case Im3d::DrawPrimitive_Triangles:
                ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                mTrianglesShader->Bind(ctx);
                mVB.Bind(ctx);
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
            AppData& ad = GetAppData();

            helios::CEngine& lEngine = helios::CEngine::GetInstance();
            helios::CWindow& lWindow = lEngine.GetWindow();

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

            Im3d::NewFrame();
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
            mImGuiShader = lEngine.GetAssetManager().Get<CShader>("imgui");

            Im3d::GetAppData().drawCallback = &Im3D_Draw;

            /*ImGuiIO& io = ImGui::GetIO();

            unsigned char* txbuf;
            int txX, txY;
            io.Fonts->GetTexDataAsAlpha8(&txbuf, &txX, &txY);
            CreateTexture2D(txX, txY, DXGI_FORMAT_R8_UNORM, &g_ImGuiFontResourceView, txbuf)->Release();

            io.Fonts->TexID = (void*)g_ImGuiFontResourceView;
            io.RenderDrawListsFn = &ImGui_Draw;*/
        }
    }
}