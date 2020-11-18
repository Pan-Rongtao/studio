#include "MainMenu.h"
#include <cstdlib>
#include "App.h"
#include "studio.h"

using namespace studio;

void MainMenu::draw()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu(u8"�ļ�")) { showMenuFile(); ImGui::EndMenu(); }
		if (ImGui::BeginMenu(u8"Edit")) { showMenuEdit(); ImGui::EndMenu(); }
		if (ImGui::BeginMenu(u8"��Դ")) { showMenuAssets(); ImGui::EndMenu(); }
		if (ImGui::BeginMenu(u8"����")) { showMenuWindows(); ImGui::EndMenu(); }
		if (ImGui::BeginMenu(u8"����")) { showMenuHelp(); ImGui::EndMenu(); }

		ImGui::EndMainMenuBar();
	}
}

void MainMenu::showMenuFile()
{
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_FILE_MEDICAL, u8"�½���Ŀ"), "Ctrl+N")) { Windows::ShowNewProjectPop = true; }
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_FOLDER_OPEN, u8"����Ŀ"), "Ctrl+O")) {}
	if (ImGui::BeginMenu(NB_ICON_TEXT(ICON_FA_HISTORY, u8"���ʹ�ù�")))
	{
		ImGui::MenuItem("1.nb");
		ImGui::MenuItem("2.nb");
		ImGui::MenuItem("3.nb");
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_BAN, u8"�ر���Ŀ"))) {}
	ImGui::Separator();

	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_SAVE, u8"����"), "Ctrl+S")) {}
	if (ImGui::MenuItem(NB_ALIGN_TEXT(u8"���Ϊ"), "Ctrl+Shift+S")) {}
	ImGui::Separator();

	if (ImGui::BeginMenu(NB_ICON_TEXT(ICON_FA_BUILDING, u8"����")))
	{
		if (ImGui::MenuItem(u8"����NBB�ļ�", "Ctrl+B")) {}
		if (ImGui::MenuItem(u8"����JSON�ļ�")) {}
		if (ImGui::MenuItem(u8"����Player���а�")) {}
		if (ImGui::MenuItem(u8"����apk")) {}
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_PLAY, u8"���벢����"), "Ctrl+R")) {  }
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_POWER_OFF, u8"�˳�"), "Ctrl+Q")) { /*std::exit(0);*/ }
}

void MainMenu::showMenuEdit()
{
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_UNDO_ALT, u8"����"), "Ctrl+Z")) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_REDO_ALT, u8"����"), "Ctrl+Y")) {}
	ImGui::Separator();
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_COPY, u8"����"), "Ctrl+C")) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_CUT, u8"����"), "Ctrl+X")) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_PASTE, u8"ճ��"), "Ctrl+V")) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_TRASH_ALT, u8"ɾ��"), "Delete")) {}
	ImGui::Separator();
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_SEARCH, u8"����"), "Ctrl+F")) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_PENCIL_ALT, u8"������"), "F2")) {}
	ImGui::Separator();
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_COG, u8"��������"))) {}
}

void MainMenu::showMenuAssets()
{
	if (ImGui::BeginMenu(NB_ICON_TEXT(ICON_FA_PLUS_CIRCLE, u8"����")))
	{
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_FOLDER_PLUS, u8"�ļ���"))) {}
		ImGui::Separator();
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_FONT, u8"����"))) {}
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_IMAGES, u8"ͼƬ"))) {}
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_SHAPES, u8"3D��Դ"))) {}
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_FILE_AUDIO, u8"Audio"), nullptr, nullptr, false)) {}
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_FILE_VIDEO, u8"Video"), nullptr, nullptr, false)) {}
		ImGui::Separator();
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_ADJUST, u8"����"))) {}
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_CHART_LINE, u8"����"))) {}
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_FOLDER, u8"���ļ�������ʾ"))) {}
	if (ImGui::MenuItem(u8"��")) {}
	if (ImGui::MenuItem(u8"ɾ��")) {}
	if (ImGui::MenuItem(u8"������")) {}
	if (ImGui::MenuItem(u8"����·��")) {}
	ImGui::Separator();
	if (ImGui::MenuItem(u8"��������Դ")) {}
}

void MainMenu::showMenuWindows()
{
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_SITEMAP, u8"�㼶����"))) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_VIDEO, u8"Ԥ������"))) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_TABLE, u8"���Դ���"))) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_ASTERISK, u8"���̴���"))) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_TERMINAL, u8"����̨����"))) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_CHART_LINE, u8"��������"))) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_DATABASE, u8"���ݴ���"))) {}
}

void MainMenu::showMenuHelp()
{
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_INFO_CIRCLE, u8"����"))) {}
	if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_GAVEL, u8"����"))) { Windows::ShowToolWindow = true; }
}
