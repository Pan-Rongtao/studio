#pragma once
#include "core/Node.hpp"

struct GLFWwindow;

namespace studio
{

	struct Windows
	{
		static bool ShowMainMenu;		//属性主菜单
		static bool ShowHierarchyWindow;//层级窗口
		static bool ShowProjectWindow;	//工程窗口
		static bool ShowPreviewWindow;	//预览窗口
		static bool ShowPropertyWindow;	//属性窗口
		static bool ShowConsoleWindow;	//控制台窗口

		static bool ShowNewProjectPop;	//新工程弹窗
	};


class App
{
public:
	static int run(int argc, char **argv);

	static NodePtr visualTreeData;

private:
	static void prepareRenderContext();
	static void render();
	static void initData();
	static void drawUI();
	static void cleanup();

	static GLFWwindow* m_glfwWindow;
};

}