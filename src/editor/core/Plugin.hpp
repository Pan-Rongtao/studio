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
		//���dll�����Ŀⲻ�ڣ�������ʧ��
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