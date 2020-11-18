#pragma once
#include "imgui/imgui.h"

namespace studio
{

class MainMenu
{
public:
	static void draw();

private:
	static void showMenuFile();
	static void showMenuEdit();
	static void showMenuAssets();
	static void showMenuWindows();
	static void showMenuHelp();
	
};

}