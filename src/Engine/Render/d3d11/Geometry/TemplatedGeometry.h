#ifndef __CTemplatedGeometry__HH__
#define __CTemplatedGeometry__HH__

#pragma once

#include "Geometry.h"

namespace render
{
    template< class TVertexType, TPrimitiveTopology >
    class CTemplatedGeometry : public CGeometry< TPrimitiveTopology >
    {
    public:
        CTemplatedGeometry(CVertexBuffer<TVertexType>* VertexBuffer)
            : CGeometry()
            , m_VertexBuffer(VertexBuffer)
        {
        }

        virtual ~CTemplatedGeometry()
        {
            delete m_VertexBuffer;
        }

        virtual void Render(CDevicePtr _device)
        {
            CGeometry::Render(_device);
            m_VertexBuffer->Bind(_device);
            _device->ImmediateContext()->Draw(m_VertexBuffer->GetNumVertexs(), 0);
        }

    protected:
        CVertexBuffer<TVertexType> *m_VertexBuffer;
    };
}

#endif
