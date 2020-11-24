#include "App.h"
#include "Plugin.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl/imgui_impl_glfw.h"
#include "imgui/imgui_impl/imgui_impl_opengl3.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ui/MainMenu.h"
#include "ui/HierarchyWindow.h"
#include "ui/ProjectWindow.h"
#include "ui/PreviewWindow.h"
#include "ui/PropertyWindow.h"
#include "ui/ConsoleWindow.h"
#include "ui/NewProjectPop.h"
#include "ui/ToolWindow.h"


using namespace studio;

bool Windows::ShowMainMenu = true;
bool Windows::ShowHierarchyWindow = true;
bool Windows::ShowProjectWindow = true;
bool Windows::ShowPreviewWindow = true;
bool Windows::ShowPropertyWindow = true; 
bool Windows::ShowConsoleWindow = true;
bool Windows::ShowToolWindow = false;

bool Windows::ShowNewProjectPop = false;

NodePtr App::visualTreeData;
GLFWwindow* App::m_glfwWindow = nullptr;

int App::run(int argc, char ** argv)
{
	auto systemPlugin = PluginManager::makePlugin("nbd");
	systemPlugin->update();

	initData();
	setup();

	render();
	
	return 0;
}

void App::setup()
{
	glfwSetErrorCallback([](int error, const char* description) {fprintf(stderr, "Glfw Error %d: %s\n", error, description); });
	assert(glfwInit());

	m_glfwWindow = glfwCreateWindow(1280, 720, "newbrush studio", nullptr, nullptr);
	assert(m_glfwWindow);

	glfwMaximizeWindow(m_glfwWindow);
	glfwMakeContextCurrent(m_glfwWindow);
	glfwSwapInterval(1); // Enable vsync

	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	// Setup Platform/Renderer backends; GL 3.0 + GLSL 130
	ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	//fonts
	io.Fonts->AddFontFromFileTTF(R"(../resource/fonts/siyuanheiti.otf)", 16.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
	io.Fonts->AddFontFromFileTTF(R"(../resource/fonts/fa-solid-900.ttf)", 16.0f, &icons_config, icons_ranges);
	io.Fonts->AddFontFromFileTTF(R"(../resource/fonts/fa-regular-400.ttf)", 16.0f, &icons_config, icons_ranges); 
	io.Fonts->AddFontFromFileTTF(R"(../resource/fonts/fa-light-300.ttf)", 16.0f, &icons_config, icons_ranges);
	io.Fonts->AddFontFromFileTTF(R"(../resource/fonts/MaterialIcons-Regular.ttf)", 16.0f, &icons_config, icons_ranges);

}

void App::render()
{
	auto imguiNewFrame = []()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		int display_w, display_h;
		glfwGetFramebufferSize(m_glfwWindow, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);
	};
	
	ImGuiIO& io = ImGui::GetIO();
	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	while (!glfwWindowShouldClose(m_glfwWindow))
	{
		glfwPollEvents();
		imguiNewFrame();

		studio::App::drawUI();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//for multi-viewport
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
		glfwSwapBuffers(m_glfwWindow);
	}

	//-----------------
	// clean up
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_glfwWindow);
	glfwTerminate();
}

void App::initData()
{
	visualTreeData;
	visualTreeData = std::make_shared<Node>("scene", type::get_by_name("nb::Scene"));
}

void App::drawUI()
{
	if (Windows::ShowMainMenu)			MainMenu::draw();
	if (Windows::ShowHierarchyWindow)	HierarchyWindow::draw();
	if (Windows::ShowProjectWindow)		ProjectWindow::draw();
	if (Windows::ShowPreviewWindow)		PreviewWindow::draw();
	if (Windows::ShowPropertyWindow)	PropertyWindow::draw();
	if (Windows::ShowConsoleWindow)		ConsoleWindow::draw();
	if (Windows::ShowToolWindow)		ToolWindow::draw();

	if (Windows::ShowNewProjectPop)		NewProjectPop::draw();

	bool show_demo_window = true;;
	if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

}
