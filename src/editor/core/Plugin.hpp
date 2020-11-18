#pragma once
#include "rttr/registration.h"
#include "rttr/library.h"

namespace studio
{

class Plugin
{
public:
	Plugin(const std::string &dllPath)
	{
		//如果dll依赖的库不在，则会加载失败
		rttr::library lib(dllPath);
		bool b = lib.load();
		if (!b)
		{
			int xx = 10;
		}
		for (auto t : lib.get_types()) // returns all registered types from this library
		{
		//	if (t.is_class() && !t.is_wrapper())
				printf("%s\n", t.get_name().data());
		}
	}

	void update();

private:
	std::string m_path;
};

}