#include "Common.h"
#include "Plugin.h"
#include "ui/StudioView.h"

using namespace studio;

int main(int argc, char** argv)
{
	auto view = new StudioView(nullptr);
	auto systemPlugin = PluginManager::makePlugin("nbd");
	systemPlugin->update();

	Datas::visualTreeData = std::make_shared<Node>("scene", type::get_by_name("nb::Scene"));

	return ImGuiHelper::run(view);
}
