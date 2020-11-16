#include "HierarchyWindow.h"
#include "imgui.h"
#include "../App.h"
#include <string>

using namespace studio;
float value;
NodePtr HierarchyWindow::visualTreeSelectedItem;

void HierarchyWindow::draw()
{
	ImGui::Begin(u8"²ã¼¶", &Windows::ShowHierarchyWindow);

	loopDraw(App::visualTreeData);
		
	ImGui::End();
}

void HierarchyWindow::loopDraw(NodePtr node)
{
	if (!node) return;

	static ImGuiTreeNodeFlags baseFlags = /*ImGuiTreeNodeFlags_OpenOnArrow | */ImGuiTreeNodeFlags_SpanFullWidth/* | ImGuiTreeNodeFlags_OpenOnDoubleClick*/;

//	ImGui::OpenPopupOnItemClick("item context menu", 1);
	bool bOpened = ImGui::TreeNodeEx(node->name.data(), visualTreeSelectedItem == node ? baseFlags | ImGuiTreeNodeFlags_Selected : baseFlags);

	showContextMenu(node->name.data());
	if (ImGui::IsItemClicked() || ImGui::IsItemFocused())
	{
		visualTreeSelectedItem = node;
	}
	if(bOpened)
	{
		for (int i = 0; i != node->childCount(); ++i)
		{
			auto child = node->at(i);
			if (child->hasChild())
			{
				loopDraw(child);
			}
			else
			{
				//ImGui::OpenPopupOnItemClick("item context menu 1", 1);
				bool isOpen = ImGui::TreeNodeEx(child->name.data(), child == visualTreeSelectedItem ? baseFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Selected : baseFlags | ImGuiTreeNodeFlags_Leaf);

				showContextMenu(child->name.data());
				if (ImGui::IsItemClicked() || ImGui::IsItemFocused())
				{
					visualTreeSelectedItem = child;
				}
				if(isOpen)
				{
					ImGui::TreePop();
				}
			}
		}

		ImGui::TreePop();
	}
}

void HierarchyWindow::showContextMenu(const char *id)
{
	if (ImGui::BeginPopupContextItem(id))
	{
		char buf[100] = "";
		sprintf(buf, "%s Set to zero", id);
		if (ImGui::Selectable(buf)) value = 0.0f;
		if (ImGui::Selectable("Set to PI")) value = 3.1415f;
		ImGui::SetNextItemWidth(-1);
		ImGui::DragFloat("##Value", &value, 0.1f, 0.0f, 0.0f);
		ImGui::EndPopup();
	}
}
