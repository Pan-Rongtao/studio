#include "ProjectWindow.h"
#include "imgui.h"
#include "../App.h"

void studio::ProjectWindow::draw()
{
	ImGui::Begin(u8"����", &Windows::ShowProjectWindow);
	ImGui::End();
}
