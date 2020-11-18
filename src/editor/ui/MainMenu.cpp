#include "MainMenu.h"
#include <cstdlib>
#include "App.h"
#include "studio.h"

using namespace studio;

void MainMenu::draw()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu(u8"文件")) { showMenuFile(); ImGui::EndMenu(); }
		if (ImGui::BeginMenu(u8"Edit")) { showMenuEdit(); ImGui::EndMenu(); }
		if (ImGui::BeginMenu(u8"资源")) { showMenuAssets(); ImGui::EndMenu(); }
		if (ImGui::BeginMenu(u8"窗口")) { showMenuWindows(); ImGui::EndMenu(); }
		if (ImGui::BeginMenu(u8"帮助")) { showMenuHelp(); ImGui::EndMenu(); }

		ImGui::EndMainMenuBar();
	}
}

void MainMenu::showMenuFile()
{
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_FILE_MEDICAL, u8"新建项目"), "Ctrl+N")) { Windows::ShowNewProjectPop = true; }
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_FOLDER_OPEN, u8"打开项目"), "Ctrl+O")) {}
	if (ImGui::BeginMenu(NB_ICON_TEXT(ICON_FA_HISTORY, u8"最近使用过")))
	{
		ImGui::MenuItem("1.nb");
		ImGui::MenuItem("2.nb");
		ImGui::MenuItem("3.nb");
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_BAN, u8"关闭项目"))) {}
	ImGui::Separator();

	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_SAVE, u8"保存"), "Ctrl+S")) {}
	if (ImGui::MenuItem(NB_ALIGN_TEXT(u8"另存为"), "Ctrl+Shift+S")) {}
	ImGui::Separator();

	if (ImGui::BeginMenu(NB_ICON_TEXT(ICON_FA_BUILDING, u8"导出")))
	{
		if (ImGui::MenuItem(u8"导出NBB文件", "Ctrl+B")) {}
		if (ImGui::MenuItem(u8"导出JSON文件")) {}
		if (ImGui::MenuItem(u8"导出Player运行包")) {}
		if (ImGui::MenuItem(u8"导出apk")) {}
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_PLAY, u8"编译并运行"), "Ctrl+R")) {  }
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_POWER_OFF, u8"退出"), "Ctrl+Q")) { /*std::exit(0);*/ }
}

void MainMenu::showMenuEdit()
{
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_UNDO_ALT, u8"撤销"), "Ctrl+Z")) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_REDO_ALT, u8"重做"), "Ctrl+Y")) {}
	ImGui::Separator();
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_COPY, u8"复制"), "Ctrl+C")) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_CUT, u8"剪切"), "Ctrl+X")) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_PASTE, u8"粘贴"), "Ctrl+V")) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_TRASH_ALT, u8"删除"), "Delete")) {}
	ImGui::Separator();
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_SEARCH, u8"查找"), "Ctrl+F")) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_PENCIL_ALT, u8"重命名"), "F2")) {}
	ImGui::Separator();
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_COG, u8"工程设置"))) {}
}

void MainMenu::showMenuAssets()
{
	if (ImGui::BeginMenu(NB_ICON_TEXT(ICON_FA_PLUS_CIRCLE, u8"创建")))
	{
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_FOLDER_PLUS, u8"文件夹"))) {}
		ImGui::Separator();
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_FONT, u8"字体"))) {}
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_IMAGES, u8"图片"))) {}
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_SHAPES, u8"3D资源"))) {}
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_FILE_AUDIO, u8"Audio"), nullptr, nullptr, false)) {}
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_FILE_VIDEO, u8"Video"), nullptr, nullptr, false)) {}
		ImGui::Separator();
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_ADJUST, u8"材质"))) {}
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_CHART_LINE, u8"动画"))) {}
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_FOLDER, u8"在文件夹中显示"))) {}
	if (ImGui::MenuItem(u8"打开")) {}
	if (ImGui::MenuItem(u8"删除")) {}
	if (ImGui::MenuItem(u8"重命名")) {}
	if (ImGui::MenuItem(u8"复制路径")) {}
	ImGui::Separator();
	if (ImGui::MenuItem(u8"导入新资源")) {}
}

void MainMenu::showMenuWindows()
{
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_SITEMAP, u8"层级窗口"))) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_VIDEO, u8"预览窗口"))) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_TABLE, u8"属性窗口"))) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_ASTERISK, u8"工程窗口"))) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_TERMINAL, u8"控制台窗口"))) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_CHART_LINE, u8"动画窗口"))) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_DATABASE, u8"数据窗口"))) {}
}

void MainMenu::showMenuHelp()
{
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_INFO_CIRCLE, u8"关于"))) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_GAVEL, u8"工具"))) { Windows::ShowToolWindow = true; }
}
