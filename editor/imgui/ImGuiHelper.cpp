#include "ImGuiHelper.h"
#include <stdio.h>
#include "imgui/imgui_impl/imgui_impl_glfw.h"
#include "imgui/imgui_impl/imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace studio;
using namespace rttr;

ImGuiView::ImGuiView(GLFWwindow * window)
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

void ImGuiView::beginFrame()
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

void ImGuiView::endFrame()
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
void ImGuiHelper::render(ImGuiView * view)
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

int ImGuiHelper::run(ImGuiView * view)
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

void ImGuiHelper::enableRender(bool b)
{
	g_enableRender = b;
}

void ImGuiWidget::showPropertyEditor(rttr::variant obj, bool * open)
{
	ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, main_viewport->GetWorkSize().y), ImGuiCond_FirstUseEver);
	ImGui::Begin(u8" Ù–‘", open);

	auto type = obj.get_type();
	auto typeName = type ? type.get_name().data() : "";
	auto props = type ? type.get_properties() : array_range<property>();

	//header
	ImVec2 button_sz(40, 40);
	ImGui::Button("", button_sz);
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(5, 5)); ImGui::SameLine();
	ImGui::Text(typeName);
	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted("");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

	ImGui::Separator();

	ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.50f);
	for (auto const &prop : props)
	{
		auto propType = prop.get_type();
		const char *propName = prop.get_name().data();

		if (propType == type::get<bool>())						{ static bool b = false; ImGui::Checkbox(propName, &b); }
		else if (propType == type::get<int>())					{ static int i0 = 0; ImGui::InputInt(propName, &i0); }
		else if (propType == type::get<float>())				{ static float f0 = 0.0f; ImGui::InputFloat(propName, &f0, 0.01f, 1.0f, "%.3f"); }
		else if (propType == type::get<double>())				{ static double d0 = 0.0; ImGui::InputDouble(propName, &d0, 0.01f, 1.0f, "%.8f"); }
		else if (propType == type::get_by_name("glm::vec2"))	{ static float f[2] = { 0.0f, 0.0f }; ImGui::InputFloat2(propName, f); }
		else if (propType == type::get_by_name("glm::vec3"))	{ static float f[3] = { 0.0f, 0.0f, 0.0f }; ImGui::InputFloat3(propName, f); }
		else if (propType == type::get_by_name("glm::vec4"))	{ static float f[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; ImGui::InputFloat4(propName, f); }
		else if (propType == type::get_by_name("nb::Color"))	{ float clr[3] = { 1.0f, 0.0f, 0.2f }; ImGui::ColorEdit3(propName, clr); }
	}
	ImGui::End();
}
