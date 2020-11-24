#pragma once
#include <string>

namespace studio
{

struct PropertyItemEditor
{
	std::string propertyName;

};

class PropertyWindow
{
public:
	static void draw();


private:
	static void showHeader();
	static void showProperties();
};


}