#include "Render.h"
#include "Engine.h"

#include "Quad.h"

#include "Device.h"

#include "Geometry.h"

namespace render
{
    CQuad::CQuad()
    {
        static std::shared_ptr< CGeometry > mGeometry = nullptr;
        if (!mGeometry)
        {
            CDevice& lDevice = helios::CEngine::GetInstance().GetDevice();
            std::vector<CScreenVertex> lVertices(4);
            lVertices[0].position = Float3(-1.0f, 1.0f, 0.5f);
            lVertices[0].uv = Float2(0.0f, 0.0f);

            lVertices[1].position = Float3(-1.0f, -1.0f, 0.5f);
            lVertices[1].uv = Float2(0.0f, 1.0f);

            lVertices[2].position = Float3(1.0f, 1.0f, 0.5f);
            lVertices[2].uv = Float2(1.0f, 0.0f);

            lVertices[3].position = Float3(1.0f, -1.0f, 0.5f);
            lVertices[3].uv = Float2(1.0f, 1.0f);

            std::shared_ptr< CVertexBuffer< CScreenVertex > > lVB = std::make_shared<CVertexBuffer<CScreenVertex>>();
            lVB->Initialize(lDevice.Device(), (CScreenVertex*)lVertices.data(), 4);
            mGeometry = std::make_shared<CGeometryTriangleStrip<CScreenVertex>>(lVB);
        }
    }

    void CQuad::Deserialize(const io::CSerializableNode& _node)
    {
        SetName(_node["name"].GetString());
    }

    void CQuad::Serialize(io::CSerializableNode& _node) const
    {

    }
}
