#include "NewProjectPop.h"
#include "App.h"
#include "studio.h"

using namespace studio;

static ImVec2 itemWidthxxx = ImVec2(0.0f, 0.0f);

void NewProjectPop::draw()
{
	ImGui::OpenPopup(u8"新建项目");
	if (ImGui::BeginPopupModal(u8"新建项目", &Windows::ShowNewProjectPop, /*ImGuiWindowFlags_NoResize |*/ ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		static char nameBuf[64] = ""; 
		//ImGui::SetKeyboardFocusHere();
		ImGui::InputText(u8"##0", nameBuf, IM_ARRAYSIZE(nameBuf));  ImGui::SameLine(); if (ImGui::Button(NB_ICON(ICON_FA_ERASER))) { memset(nameBuf, 0, IM_ARRAYSIZE(nameBuf)); }
		
		static char localionBuf[256] = "";
		ImGui::InputText(u8"##1", localionBuf, IM_ARRAYSIZE(localionBuf)); ImGui::SameLine(); ImGui::Button(NB_ICON( ICON_FA_ELLIPSIS_H ));

		if (ImGui::Button(u8"取消", ImVec2(-ImGui::GetWindowWidth() / 2.0f, 0.0f))) {}
		ImGui::SameLine();
		if (ImGui::Button(u8"创建", ImVec2(-FLT_MIN, 0.0f))) {}

		ImGui::EndPopup();
	}
}
