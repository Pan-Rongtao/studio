#pragma once
#include "rttr/registration.h"
#include "rttr/library.h"
#include <tuple>
//#include "newbrush/model/RttrRegistration.h"
//#include "newbrush/model/Object.h"
//一定不要include nb相关的头文件，否则rttr::library读取不到任何注册的type信息，
//包含的头文件与nb无关则没事，原因不明
//可能：包含了nb相关的头文件，nb库有RTTR注册的宏，会自动加载注册信息，直接读取type::get_types()即可
//目前不采用读取dll的方式，否则无法再使用nb的接口，这两者互斥

using namespace rttr;

namespace studio
{

struct ClassMetaInfo
{
	std::string name;
	std::string icon;
	std::string description;
};

class Plugin
{
public:
	Plugin(const std::string &dllPath) : m_path(dllPath) {}

	bool isEnum(type t)		{ return t.is_enumeration(); }
	bool isClass(type t)	{ return t.is_class() && !t.is_wrapper(); }
	bool isVisual(type t)	
	{ 
		static type visualT = type::get_by_name("nb::Visual");
		auto meta = t.get_metadata("ClassMeta");
		return (t != visualT && t.is_derived_from(visualT)) && (meta.is_type<std::tuple<std::string, std::string, std::string>>());
	}

	bool update()
	{
		//如果dll依赖的库不在，则会加载失败
		rttr::library lib(m_path);
		if (!lib.load()) return false;
		auto types = lib.get_types();

		//auto types = type::get_types();
		for (auto t : type::get_types())
		{
			if (isClass(t) && isVisual(t))
			{
				printf("%s\n", t.get_name().data());
				auto meta = t.get_metadata("ClassMeta").get_value<std::tuple<std::string, std::string, std::string>>();
				visuals.insert({ t, {std::get<0>(meta), std::get<1>(meta), std::get<2>(meta)} });
			}
		}
		return true;
	}

	std::map<type, ClassMetaInfo> visuals;

private:
	std::string m_path;
	friend class PluginManager;
};

using PluginPtr = std::shared_ptr<Plugin>;

class PluginManager
{
public:
	static PluginPtr makePlugin(const std::string &dllPath);

	static std::vector<PluginPtr> plugins;
};

}