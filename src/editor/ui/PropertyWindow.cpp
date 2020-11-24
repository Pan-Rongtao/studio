#include "PropertyWindow.h"
#include "imgui.h"
#include "../App.h"
#include "HierarchyWindow.h"
#include "glm/glm.hpp"
#include "core/Plugin.h"

using namespace studio;
using namespace rttr;

void PropertyWindow::draw()
{
	ImGui::Begin(u8"ÊôÐÔ", &Windows::ShowPropertyWindow);

	showProperties();

	ImGui::End();
}

static void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void PropertyWindow::showProperties()
{
	if (!HierarchyWindow::visualTreeSelectedItem)	return;

	auto selectType = HierarchyWindow::visualTreeSelectedItem->type;

	//header
	{
		auto pluginVisuals = PluginManager::plugins[0]->visuals;
		auto iter = pluginVisuals.find(selectType);
		if (iter != pluginVisuals.end())
		{
			ImVec2 button_sz(40, 40);
			ImGui::Button(iter->second.icon.data(), button_sz);
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(5, 5)); ImGui::SameLine();
			ImGui::Text(iter->second.name.data());
			ImGui::SameLine();
			HelpMarker(iter->second.description.data());
		}
	}
	
	ImGui::Separator();

	for (auto const &prop : selectType.get_properties())
	{
		auto propType = prop.get_type();
		const char *propName = prop.get_name().data();
		if (propType == type::get<bool>())
		{
			static bool b = false;
			ImGui::Checkbox(propName, &b);
		}
		else if (propType == type::get<int>())
		{
			static int i0 = 0;
			ImGui::InputInt(propName, &i0);
		}
		else if (propType == type::get<float>())
		{
			static float f0 = 0.0f;
			ImGui::InputFloat(propName, &f0, 0.01f, 1.0f, "%.3f");
		}
		else if (propType == type::get<double>())
		{
			static double d0 = 0.0;
			ImGui::InputDouble(propName, &d0, 0.01f, 1.0f, "%.8f");
		}
		else if (propType == type::get<glm::vec2>())
		{
			static float f[2] = {0.0f, 0.0f};
			ImGui::InputFloat2(propName, f);
		}
		else if (propType == type::get<glm::vec3>())
		{
			static float f[3] = { 0.0f, 0.0f, 0.0f };
			ImGui::InputFloat3(propName, f);
		}
		else if (propType == type::get<glm::vec4>())
		{
			static float f[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			ImGui::InputFloat4(propName, f);
		}
		else if (propType == type::get_by_name("nb::Color"))
		{
			float clr[3] = { 1.0f, 0.0f, 0.2f };
			ImGui::ColorEdit3(propName, clr);
		}
	}

}
