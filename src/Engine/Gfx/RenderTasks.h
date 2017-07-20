#pragma once
#include "Gfx.h"

#include "Core/Name.h"
#include "Core/Enabled.h"
#include "Core/Utils/Containers.h"
#include "Core/Utils/Objectfactory.h"

namespace gfx
{
    struct CRenderTask : public core::CName, public core::CEnabled
    {
        SERIALIZABLE_OBJECT
        virtual void Execute() = 0;
        virtual void OnEditor();
    };

    struct CBeginFrame : public CRenderTask
    {
        SERIALIZABLE_OBJECT
        virtual void Execute();
        virtual void OnEditor();
    };

    struct CEndFrame : public CRenderTask
    {
      SERIALIZABLE_OBJECT
      virtual void Execute();
      virtual void OnEditor();
    };

    struct CRenderDebugText : public CRenderTask
    {
        SERIALIZABLE_OBJECT
        virtual void Execute();
        virtual void OnEditor();
        core::CStr mText;
        uint32_t mX;
        uint32_t mY;
    };

    struct CSetViewport : public CRenderTask
    {
      SERIALIZABLE_OBJECT
      virtual void Execute();
      virtual void OnEditor();
      core::CStr mText;
      uint32_t mX;
      uint32_t mY;
    };

    struct CClear : public CRenderTask
    {
      SERIALIZABLE_OBJECT
      virtual void Execute();
      virtual void OnEditor();
      CColor mColor;
      uint32_t mColorEncoded;
      uint16_t mFlags;
      bool mClearColor;
      bool mClearDepth;
      bool mClearStencil;
      float mDepthValue;
      uint8_t mStencil;
    };
}