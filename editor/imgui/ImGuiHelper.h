#pragma once
#define NOMINMAX
#include <stdio.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl/imgui_impl_glfw.h"
#include "imgui/imgui_impl/imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace studio
{
	
class ImGuiView
{
public:
	ImGuiView(GLFWwindow *window);
	virtual ~ImGuiView() = default;

	virtual void onInit() {}
	virtual void onRender() {}

	GLFWwindow *getWindow() const { return m_window; }

private:
	void beginFrame();
	void endFrame();

	GLFWwindow *m_window;
	friend class ImGuiHelper;
};

class ImGuiHelper
{
public:
	static void render(ImGuiView *view);
	static int run(ImGuiView *view);
	static void enableRender(bool b);
};

inline ImGuiView::ImGuiView(GLFWwindow * window)
{
	if (!window)
	{
		glfwSetErrorCallback([](int error, const char* description) { fprintf(stderr, "Glfw Error %d: %s\n", error, description); });
		glfwInit();

		auto monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		window = glfwCreateWindow(mode->width, mode->height, "newbrush studio", nullptr, nullptr);

		glfwMaximizeWindow(window);
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // Enable vsync
	}
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	m_window = window;

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	// Setup Platform/Renderer backends; GL 3.0 + GLSL 130
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

}

inline void ImGuiView::beginFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	int display_w, display_h;
	glfwGetFramebufferSize(m_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	//	glClear(GL_COLOR_BUFFER_BIT);
}

inline void ImGuiView::endFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	//for multi-viewport
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

static bool g_enableRender = true;
inline void ImGuiHelper::render(ImGuiView * view)
{
	if (!view || !g_enableRender)
		return;

	static bool viewInited = false;
	if (!viewInited)
	{
		view->onInit();
		viewInited = true;
	}

	view->beginFrame();
	view->onRender();
	view->endFrame();
}

inline int ImGuiHelper::run(ImGuiView * view)
{
	if (!view)
		return -1;

	auto window = view->getWindow();
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		ImGuiHelper::render(view);

		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

inline void ImGuiHelper::enableRender(bool b)
{
	g_enableRender = b;
}

}