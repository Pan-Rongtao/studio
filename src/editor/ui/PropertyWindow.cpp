#include "PropertyWindow.h"
#include "imgui.h"
#include "../App.h"

void studio::PropertyWindow::draw()
{
	ImGui::Begin(u8"����", &Windows::ShowPropertyWindow);


	ImGui::End();
}
