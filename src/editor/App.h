#pragma once
#include "core/Node.hpp"
#include "studio.h"

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
		static bool ShowToolWindow;		//�¹��̵���

		static bool ShowNewProjectPop;	//�¹��̵���
	};


class App
{
public:
	static int run(int argc, char **argv);

	static NodePtr visualTreeData;

private:
	static void setup();
	static void render();
	static void initData();
	static void drawUI();

	static GLFWwindow* m_glfwWindow;
};

}