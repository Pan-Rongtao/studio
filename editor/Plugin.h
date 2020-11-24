#pragma once
#include "rttr/registration.h"
#include "rttr/library.h"
#include <tuple>
//#include "newbrush/model/RttrRegistration.h"
//#include "newbrush/model/Object.h"
//һ����Ҫinclude nb��ص�ͷ�ļ�������rttr::library��ȡ�����κ�ע���type��Ϣ��
//������ͷ�ļ���nb�޹���û�£�ԭ����
//���ܣ�������nb��ص�ͷ�ļ���nb����RTTRע��ĺ꣬���Զ�����ע����Ϣ��ֱ�Ӷ�ȡtype::get_types()����
//Ŀǰ�����ö�ȡdll�ķ�ʽ�������޷���ʹ��nb�Ľӿڣ������߻���

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
		//���dll�����Ŀⲻ�ڣ�������ʧ��
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