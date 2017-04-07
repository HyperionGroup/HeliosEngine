#pragma once

#include "RenderableView.h"

namespace user
{
    class CSceneView : public CRenderableView
    {
    public:
        CSceneView( QWidget* _parent );
        virtual ~CSceneView();
    protected:
        CRenderableView* mView;
    };
}