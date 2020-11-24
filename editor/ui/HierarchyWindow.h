#pragma once
#include "Node.h"

namespace studio
{

class HierarchyWindow
{
public:
	static void draw();

	static NodePtr visualTreeSelectedItem;

private:
	static void loopDraw(NodePtr node);
	static void showContextMenu(const char *id);
};


}