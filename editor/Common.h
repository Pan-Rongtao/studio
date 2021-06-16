#pragma once
#include <string>
#include "Node.h"
#include "fontcpp/IconsFontAwesome5Pro.h"
#include "fontcpp/IconsMaterialDesign.h"

namespace studio
{

//icon check: http://www.wapadd.cn/icons/awesome/index.htm
static std::string makeIconText(const char *icon, const char *join, const char *text)
{
	char buf[80] = { 0 }; sprintf(buf, "%s%s%s", icon, join, text);
	return buf;
}

#ifdef _WIN32
#define NB_NEWLINE  "\r\n"
#else
#define NB_NEWLINE  "\n"
#endif

#define NB_ICON_TEXT(icon, text)	makeIconText(icon, "\t", text).data()
#define NB_ALIGN_TEXT(text)			makeIconText("\t", "\t", text).data()
#define NB_ICON(icon)				makeIconText(icon, "", "").data()

struct Datas
{
	static bool ShowMainMenu;		//�������˵�
	static bool ShowHierarchyWindow;//�㼶����
	static bool ShowProjectWindow;	//���̴���
	static bool ShowPreviewWindow;	//Ԥ������
	static bool ShowPropertyWindow;	//���Դ���
	static bool ShowConsoleWindow;	//����̨����
	static bool ShowToolWindow;		//�¹��̵���

	static bool ShowNewProjectPop;	//�¹��̵���

	static NodePtr visualTreeData;
};

}