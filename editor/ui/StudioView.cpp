#include "StudioView.h"
#include "Common.h"
#include "ui/MainMenu.h"
#include "ui/HierarchyWindow.h"
#include "ui/ProjectWindow.h"
#include "ui/PreviewWindow.h"
#include "ui/ConsoleWindow.h"
#include "ui/NewProjectPop.h"
#include "ui/ToolWindow.h"
#include "ImGuiHelper.h"

using namespace rttr;

void studio::StudioView::onInit()
{
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags &= ~(ImGuiConfigFlags_ViewportsEnable);
	//fonts
	io.Fonts->AddFontFromFileTTF(R"(../resource/fonts/siyuanheiti.otf)", 16.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
	io.Fonts->AddFontFromFileTTF(R"(../resource/fonts/fa-solid-900.ttf)", 16.0f, &icons_config, icons_ranges);
	io.Fonts->AddFontFromFileTTF(R"(../resource/fonts/fa-regular-400.ttf)", 16.0f, &icons_config, icons_ranges);
	io.Fonts->AddFontFromFileTTF(R"(../resource/fonts/fa-light-300.ttf)", 16.0f, &icons_config, icons_ranges);
	io.Fonts->AddFontFromFileTTF(R"(../resource/fonts/MaterialIcons-Regular.ttf)", 16.0f, &icons_config, icons_ranges);

}

void studio::StudioView::onRender()
{
	variant v;

	if (Datas::ShowMainMenu)			MainMenu::draw();
	if (Datas::ShowHierarchyWindow)	HierarchyWindow::draw();
	if (Datas::ShowProjectWindow)		ProjectWindow::draw();
	if (Datas::ShowPreviewWindow)		PreviewWindow::draw();
	if (Datas::ShowPropertyWindow)	ImGuiWidget::showPropertyEditor(v, &Datas::ShowPropertyWindow);
	if (Datas::ShowConsoleWindow)		ConsoleWindow::draw();
	if (Datas::ShowToolWindow)		ToolWindow::draw();

	if (Datas::ShowNewProjectPop)		NewProjectPop::draw();

	bool show_demo_window = true;;
	if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);
}
