#ifndef _RENDERABLE_VERTEXS_HH_
#define _RENDERABLE_VERTEXS_HH_

#pragma once

namespace render
{
    template < typename TPrimitiveTopology >
    class CGeometry
    {
    public:
        CGeometry() {}
        virtual ~CGeometry() {}

        virtual void Render(CDevicePtr _device)
        {
            // Configure the type of topology to be renderer ( p.e. Triangles, Quads, points,... )
            _device->ImmediateContext()->IASetPrimitiveTopology(TPrimitiveTopology);
        }

        virtual void RenderIndexed(CDevicePtr _device, uint32 _indexCount = -1, uint32 _startIndexLocation = 0, uint32 _baseVertexLocation = 0)
        {
            // Configure the type of topology to be renderer ( p.e. Triangles, Quads, points,... )
            _device->ImmediateContext()->IASetPrimitiveTopology(TPrimitiveTopology);
            HELIOSUNUSED(_indexCount);
            HELIOSUNUSED(_startIndexLocation);
            HELIOSUNUSED(_baseVertexLocation);
        }
    };
}

#endif
