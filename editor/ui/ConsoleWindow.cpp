#include "ConsoleWindow.h"
#include "Common.h"

using namespace studio;

ExampleAppLog ConsoleWindow::m_log;
void ConsoleWindow::draw()
{
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
	ImGui::Begin(u8"����̨", &Datas::ShowConsoleWindow);

	if (ImGui::SmallButton(u8"����Log"))
	{
		info("this is a info message.");
		warn("this is a warn message.");
		error("this is a error message.");
	}

	ImGui::End();

	m_log.Draw(u8"����̨", &Datas::ShowConsoleWindow);
}
