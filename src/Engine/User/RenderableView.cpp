#pragma once

#include "RenderableView.h"
#include "d3d11\RenderContext.h"
#include "qwindowdefs.h"
#include <QObject>
#include <QTimer>

namespace user
{
    CRenderableView::CRenderableView( QWidget* _parent )
        : QWidget( _parent )
        , currentTimeDeltaSample(0)
    {
        setBackgroundRole(QPalette::NoRole);
        setAttribute(Qt::WA_PaintOnScreen);
        setAttribute(Qt::WA_NoSystemBackground);
        setAttribute(Qt::WA_NativeWindow);
        setAttribute(Qt::WA_OpaquePaintEvent);

        QTimer* timer = new QTimer(this);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(render()));
        timer->start(16);
    }

    CRenderableView::~CRenderableView()
    {
    }

    HWND CRenderableView::GetHWND()
    {
        return (HWND)winId();
    }

    void CRenderableView::render()
    {
        timer.Update();

        CalculateFPS();

        float dt = timer.DeltaSecondsF();

        float clearColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
        render::CRenderContext::GetInstance().ClearColor(clearColor);
        render::CRenderContext::GetInstance().SwapBuffers();
    }

    void CRenderableView::resizeEvent(QResizeEvent* evt)
    {
        render::CRenderContext::GetInstance().Resize(width(), height());
    }

    void CRenderableView::paintEvent(QPaintEvent* evt)
    {
    }

    void CRenderableView::CalculateFPS()
    {
        timeDeltaBuffer[currentTimeDeltaSample] = timer.DeltaSecondsF();
        currentTimeDeltaSample = (currentTimeDeltaSample + 1) % NumTimeDeltaSamples;

        float averageDelta = 0;
        for (UINT i = 0; i < NumTimeDeltaSamples; ++i)
            averageDelta += timeDeltaBuffer[i];
        averageDelta /= NumTimeDeltaSamples;

        fps = static_cast<UINT>(std::floor((1.0f / averageDelta) + 0.5f));
        printf("FPS:%d\n",fps);
    }
}