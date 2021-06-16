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
	static bool ShowMainMenu;		//属性主菜单
	static bool ShowHierarchyWindow;//层级窗口
	static bool ShowProjectWindow;	//工程窗口
	static bool ShowPreviewWindow;	//预览窗口
	static bool ShowPropertyWindow;	//属性窗口
	static bool ShowConsoleWindow;	//控制台窗口
	static bool ShowToolWindow;		//新工程弹窗

	static bool ShowNewProjectPop;	//新工程弹窗

	static NodePtr visualTreeData;
};

}