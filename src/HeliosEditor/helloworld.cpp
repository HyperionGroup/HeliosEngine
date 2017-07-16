
#include <bx/uint32_t.h>
#include "common.h"
#include "bgfx_utils.h"
#include "logo.h"
#include "entry/input.h"
#include "imgui/imgui.h"
#include "Logic/Script.h"

#include "Core/Serialization.h"
#include "Gfx/Pipeline.h"
#include "Gfx/Window.h"
#include "Core/Editor/EditorManager.h"
#include <QApplication>
#include <QTextEdit>

#include <bgfx\platform.h>

namespace
{
  void darkTheme()
  {
    ImGuiStyle& mStyle = ImGuiStyle();
    mStyle.WindowMinSize = ImVec2(160, 20);
    mStyle.FramePadding = ImVec2(4, 2);
    mStyle.ItemSpacing = ImVec2(6, 2);
    mStyle.ItemInnerSpacing = ImVec2(6, 4);
    mStyle.Alpha = 0.95f;
    mStyle.WindowRounding = 4.0f;
    mStyle.FrameRounding = 2.0f;
    mStyle.IndentSpacing = 6.0f;
    mStyle.ItemInnerSpacing = ImVec2(2, 4);
    mStyle.ColumnsMinSpacing = 50.0f;
    mStyle.GrabMinSize = 14.0f;
    mStyle.GrabRounding = 16.0f;
    mStyle.ScrollbarSize = 12.0f;
    mStyle.ScrollbarRounding = 16.0f;

    ImGuiStyle& style = mStyle;
    style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.28f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.58f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.92f, 0.18f, 0.29f, 0.76f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_Column] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
    style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
    style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_CloseButton] = ImVec4(0.86f, 0.93f, 0.89f, 0.16f);
    style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.86f, 0.93f, 0.89f, 0.39f);
    style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.9f);
    style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f);
  }

  inline void winSetHwnd(::HWND _window)
  {
    bgfx::PlatformData pd;
    bx::memSet(&pd, 0, sizeof(pd));
    pd.nwh = _window;
    bgfx::setPlatformData(pd);
  }
}

class ExampleHelloWorld : public entry::AppI
{
public:
  ExampleHelloWorld(const char* _name, const char* _description)
    : entry::AppI(_name, _description)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) BX_OVERRIDE
	{
    gfx::CWindow::GetInstance().Init(_argc, _argv, _width, _height);
    m_RenderPipeline.Deserialize();
		imguiCreate();

    bgfx::setViewClear(0
      , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
      , 0xff3030ff
      , 1.0f
      , 0
    );

    //darkTheme();
	}

	virtual int shutdown() BX_OVERRIDE
	{
		imguiDestroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() BX_OVERRIDE
	{
		if (!gfx::CWindow::GetInstance().Update() )
		{
      editor::CEditorManager::GetInstance().Update();
      m_RenderPipeline.Execute();
     
			return true;
		}

		return false;
	}

  gfx::CRenderPipeline m_RenderPipeline;
  std::shared_ptr< QApplication > mQtApplication;
};

//ENTRY_IMPLEMENT_MAIN(ExampleHelloWorld, "00-helloworld", "Initialization and debug text.");


/*
int main(int argv, char **args)
{
  QApplication app(argv, args);

  QWidget myWIdget;

  //bgfx::setPlatformData(data);
  bgfx::init();
  bgfx::PlatformData data;
  data.nwh = (void*)myWIdget.winId();

  myWIdget.show();

  return app.exec();
}*/