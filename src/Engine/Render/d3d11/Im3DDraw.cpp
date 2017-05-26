#include "Render.h"
#include "Im3DDraw.h"

#include "Device.h"
#include "Geometry/Vertex.h"
#include "Buffers/ConstantBuffer.h"
#include "Shaders/ShaderStages/VertexStage.h"
#include "Buffers/DynamicVertexBuffer.h"

#include "Engine.h"

#include "Shaders/Shader.h"

namespace render
{ 
    namespace Im3d_Draw
    {
        struct Layout
        {
            Float4x4 mViewProj;
            Float2 mViewport;
        };

        CConstantBuffer< Layout > mCB;
        CDynamicVertexBuffer< Im3d::VertexData > mVB;
        std::shared_ptr<CShader> mPointsShader;
        std::shared_ptr<CShader> mLinesShader;
        std::shared_ptr<CShader> mTrianglesShader;

        void Im3d_Draw::Initialize()
        {
            helios::CEngine& lEngine = helios::CEngine::GetInstance();
            CDevice& lDevice = lEngine.GetDevice();

            ID3D11Device* d3d = lDevice.Device();
            ID3D11DeviceContext* ctx = lDevice.ImmediateContext();

            mCB.Initialize(d3d);

            mPointsShader    = lEngine.GetAssetManager().Get<CShader>("im3d_points_shader");
            mLinesShader     = lEngine.GetAssetManager().Get<CShader>("im3d_lines_shader");
            mTrianglesShader = lEngine.GetAssetManager().Get<CShader>("im3d_triangles_shader");

            Im3d::GetAppData().drawCallback = &Draw;
        }

        void Im3d_Draw::ShutDown()
        {

        }

        void Im3d_Draw::Draw(const Im3d::DrawList& _drawList)
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

            mCB.Data.mViewport = ad.m_viewportSize;
            // TODO: Obtain main camera view proj
            // sIm3DConstantBuffer.Data.mViewProj = 

            mCB.Apply(ctx);

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

            mCB.BindVS(ctx, 0);

            // select shader/primitive topo
            switch (_drawList.m_primType)
            {
            case Im3d::DrawPrimitive_Points:
                ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
                mPointsShader->Bind(ctx);
                mCB.BindGS(ctx, 0);
                mVB.Bind(ctx);
                ctx->Draw(_drawList.m_vertexCount, 0);
                mPointsShader->Unbind(ctx);
                break;
            case Im3d::DrawPrimitive_Lines:
                ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
                mLinesShader->Bind(ctx);
                mCB.BindGS(ctx, 0);
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
    }
}