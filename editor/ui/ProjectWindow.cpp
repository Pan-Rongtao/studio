#include "ProjectWindow.h"
#include "imgui.h"
#include "Common.h"

void studio::ProjectWindow::draw()
{
	ImGui::Begin(u8"����", &Datas::ShowProjectWindow);
	ImGui::End();
}
