#include "HierarchyWindow.h"
#include "imgui.h"
#include "Common.h"
#include <string>
#include "Plugin.h"
#include "ui/ConsoleWindow.h"

using namespace studio;
float value;
NodePtr HierarchyWindow::visualTreeSelectedItem;

void HierarchyWindow::draw()
{
	ImGui::Begin(u8"层级", &Datas::ShowHierarchyWindow);

	loopDraw(Datas::visualTreeData);
	
	ImGui::End();
}

void HierarchyWindow::loopDraw(NodePtr node)
{
	static auto isItemHandling = []()
	{
		return ImGui::IsItemClicked() || ImGui::IsItemFocused() || (ImGui::IsItemHovered(ImGuiHoveredFlags_None) && ImGui::IsMouseReleased(1));
	};

	if (!node) return;

	static ImGuiTreeNodeFlags baseFlags = /*ImGuiTreeNodeFlags_OpenOnArrow | */ImGuiTreeNodeFlags_SpanFullWidth/* | ImGuiTreeNodeFlags_OpenOnDoubleClick*/;
	auto flags = visualTreeSelectedItem == node ? baseFlags | ImGuiTreeNodeFlags_Selected : baseFlags;
	if (!node->hasChild()) flags |= ImGuiTreeNodeFlags_Leaf;
	bool bOpened = ImGui::TreeNodeEx(node->name.data(), flags);

	showContextMenu(node->name.data());
	if (isItemHandling())
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
				bool isOpen = ImGui::TreeNodeEx(child->name.data(), child == visualTreeSelectedItem ? baseFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Selected : baseFlags | ImGuiTreeNodeFlags_Leaf);

				showContextMenu(child->name.data());
				if (isItemHandling())
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
		if (ImGui::BeginMenu(NB_ICON_TEXT(ICON_FA_PLUS_CIRCLE, u8"添加")))
		{
			for (auto plugin : PluginManager::plugins)
			{
				for (auto one : plugin->visuals)
				{
					auto const &type = one.first;
					auto const &name = one.second.name;
					auto const &icon = one.second.icon;
					auto const &description = one.second.description;
					bool click = ImGui::MenuItem(makeIconText(icon.data(), "\t", name.data()).data());
					if (click)
					{
						ConsoleWindow::info("add item {}", name.data());
						auto newNode = std::make_shared<Node>(name, type);
						visualTreeSelectedItem->addChild(newNode);
					//	ImGui::SetNextTreeNodeOpen(true);
						break;
					}
				}
			}
			ImGui::EndMenu();
		}
		ImGui::Separator();
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_PENCIL_ALT, u8"重命名"), "F2")) {}
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_COPY, u8"复制"), "Ctrl+C")) {}
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_CUT, u8"剪切"), "Ctrl+X")) {}
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_PASTE, u8"粘贴"), "Ctrl+V")) {}
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_TRASH_ALT, u8"删除"), "Delete")) {}
		ImGui::Separator();
		if (ImGui::MenuItem(NB_ICON_TEXT(ICON_FA_EXPAND_ALT, u8"展开/收起"), "Ctrl+G")) {}

		ImGui::EndPopup();
	}
}
