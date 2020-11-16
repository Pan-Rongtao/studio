#pragma once
#include "core/Node.hpp"

struct GLFWwindow;

namespace studio
{

	struct Windows
	{
		static bool ShowMainMenu;		//�������˵�
		static bool ShowHierarchyWindow;//�㼶����
		static bool ShowProjectWindow;	//���̴���
		static bool ShowPreviewWindow;	//Ԥ������
		static bool ShowPropertyWindow;	//���Դ���
		static bool ShowConsoleWindow;	//����̨����

		static bool ShowNewProjectPop;	//�¹��̵���
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