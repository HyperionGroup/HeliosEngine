#pragma once

#include <QWidget>
#include "Timer.h"
#include "Types.h"

namespace user
{
    class CRenderableView : public QWidget
    {
        Q_OBJECT
    public:
        CRenderableView( QWidget* _parent );
        virtual ~CRenderableView();
        QPaintEngine *paintEngine() { return NULL; }
        HWND GetHWND();
    protected slots:
        void render();
    protected:
        virtual void resizeEvent(QResizeEvent* evt);
        virtual void paintEvent(QPaintEvent* evt);
        void CalculateFPS();
        static const uint32 NumTimeDeltaSamples = 64;
        float timeDeltaBuffer[NumTimeDeltaSamples];
        uint32 currentTimeDeltaSample;
        uint32 fps;
        Timer timer;
    };
}