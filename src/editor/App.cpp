#include "App.h"
#include "imgui/imgui.h"
#include "ui/imgui_impl/imgui_impl_glfw.h"
#include "ui/imgui_impl/imgui_impl_opengl2.h"
#include <GLFW/glfw3.h>
#include "ui/fontcpp/IconsFontAwesome5.h"
#include "ui/MainMenu.h"
#include "ui/HierarchyWindow.h"
#include "ui/ProjectWindow.h"
#include "ui/PreviewWindow.h"
#include "ui/PropertyWindow.h"
#include "ui/ConsoleWindow.h"
#include "ui/NewProjectPop.h"

using namespace studio;

bool Windows::ShowMainMenu = true;
bool Windows::ShowHierarchyWindow = true;
bool Windows::ShowProjectWindow = true;
bool Windows::ShowPreviewWindow = true;
bool Windows::ShowPropertyWindow = true;
bool Windows::ShowConsoleWindow = true;

bool Windows::ShowNewProjectPop = false;

NodePtr App::visualTreeData;
GLFWwindow* App::m_glfwWindow = nullptr;

int App::run(int argc, char ** argv)
{
	initData();

	prepareRenderContext();
	render();

	cleanup();

	return 0;
}

void App::prepareRenderContext()
{
	glfwSetErrorCallback([](int error, const char* description) {fprintf(stderr, "Glfw Error %d: %s\n", error, description); });
	assert(glfwInit());

	m_glfwWindow = glfwCreateWindow(1280, 720, "newbrush studio", nullptr, nullptr);
	assert(m_glfwWindow);

	glfwMaximizeWindow(m_glfwWindow);
	glfwMakeContextCurrent(m_glfwWindow);
	glfwSwapInterval(1); // Enable vsync
						 
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, true);
	ImGui_ImplOpenGL2_Init();

	//fonts
	io.Fonts->AddFontFromFileTTF(R"(../../../../resource/fonts/siyuanheiti.otf)", 16.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());

	// merge in icons from Font Awesome
	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
	io.Fonts->AddFontFromFileTTF(R"(../../../../resource/fonts/fa-solid-900.ttf)", 16.0f, &icons_config, icons_ranges);
	io.Fonts->AddFontFromFileTTF(R"(../../../../resource/fonts/fa-regular-400.ttf)", 16.0f, &icons_config, icons_ranges);
	//io.Fonts->AddFontFromFileTTF(R"(../../../../resource/fonts/fa-light-300.ttf)", 16.0f, &icons_config, icons_ranges);
	// use FONT_ICON_FILE_NAME_FAR if you want regular instead of solid

}

void App::render()
{
	auto newFrame = []()
	{
		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	};

	auto swapBuffer = [](ImGuiIO& io)
	{
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(m_glfwWindow, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
		glfwSwapBuffers(m_glfwWindow);
	};

	ImGuiIO& io = ImGui::GetIO();
	while (!glfwWindowShouldClose(m_glfwWindow))
	{
		glfwPollEvents();
		newFrame();

		bool show_demo_window = true;;
		if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

		studio::App::drawUI();

		swapBuffer(io);
	}
}

void App::initData()
{
	visualTreeData;
	visualTreeData = std::make_shared<Node>("root");
	visualTreeData->addChild(std::make_shared<Node>("0"));
	visualTreeData->addChild(std::make_shared<Node>("1"));
	visualTreeData->addChild(std::make_shared<Node>("2"));
	//visualTreeData->get("1")->addChild(std::make_shared<Node>("1_0"));
	//visualTreeData->get("1")->addChild(std::make_shared<Node>("1_1"));
	//visualTreeData->get("1")->addChild(std::make_shared<Node>("1_2"));
	visualTreeData->get("2")->addChild(std::make_shared<Node>("2_0"));
	visualTreeData->get("2")->addChild(std::make_shared<Node>("2_1"));
}

void App::drawUI()
{
	if (Windows::ShowMainMenu)			MainMenu::draw();
	if (Windows::ShowHierarchyWindow)	HierarchyWindow::draw();
	if (Windows::ShowProjectWindow)		ProjectWindow::draw();
	if (Windows::ShowPreviewWindow)		PreviewWindow::draw();
	if (Windows::ShowPropertyWindow)	PropertyWindow::draw();
	if (Windows::ShowConsoleWindow)		ConsoleWindow::draw();

	if (Windows::ShowNewProjectPop)		NewProjectPop::draw();
}

void App::cleanup()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_glfwWindow);
	glfwTerminate();
}