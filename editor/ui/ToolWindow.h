#pragma once
#include "imgui/imgui.h"

namespace studio
{

class ToolWindow
{
public:
	static void draw();

private:
	static void helpMarker(const char* desc);
	static void nodeFont(ImFont* font);
	static void showStyleEditor(ImGuiStyle* ref = nullptr);
};

}