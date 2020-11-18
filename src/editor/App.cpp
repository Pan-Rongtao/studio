#include "App.h"
#include "core/Plugin.hpp"
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
	Plugin p("modeld");

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

}
#include <iostream>

void prepareTriangleData(int &program, uint32_t &vao)
{
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 0.2f);\n"
		"}\n\0";
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	// check for linking errors
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, // right 
		0.0f,  0.5f, 0.0f  // top   
	};

	unsigned int VBO;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void drawTriangle(int program, uint32_t vao)
{
	// draw our first triangle
	glUseProgram(program);
	glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void App::render()
{
	auto imguiNewFrame = []()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		int display_w, display_h;
		glfwGetFramebufferSize(m_glfwWindow, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);
	};

	int program;
	uint32_t vao;
	prepareTriangleData(program, vao);

	ImGuiIO& io = ImGui::GetIO();
	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	while (!glfwWindowShouldClose(m_glfwWindow))
	{
		glfwPollEvents();
		imguiNewFrame();

		studio::App::drawUI();
		drawTriangle(program, vao);

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
	if (Windows::ShowToolWindow)		ToolWindow::draw();

	if (Windows::ShowNewProjectPop)		NewProjectPop::draw();

	bool show_demo_window = true;;
	if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

}
