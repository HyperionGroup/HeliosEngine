#pragma once

#include "SceneView.h"
#include "RenderableView.h"

namespace user
{
    CSceneView::CSceneView(QWidget* _parent)
        : CRenderableView( _parent)
    {
    }

    CSceneView::~CSceneView()
    {

    }
}