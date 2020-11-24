#include "PreviewWindow.h"
#include "imgui.h"
#include "../App.h"

void studio::PreviewWindow::draw()
{
	ImGui::Begin(u8"‘§¿¿", &Windows::ShowPreviewWindow);
	ImGui::End();
}
