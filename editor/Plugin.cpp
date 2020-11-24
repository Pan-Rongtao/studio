#include "Plugin.h"

using namespace studio;

std::vector<PluginPtr> PluginManager::plugins;

PluginPtr PluginManager::makePlugin(const std::string & dllPath)
{
	auto p = std::make_shared<Plugin>(dllPath);
	plugins.push_back(p);
	return p;
}
