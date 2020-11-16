#pragma once
#include <string>
#include "ui/fontcpp/IconsFontAwesome5.h"

namespace studio
{
	//icon check: http://www.wapadd.cn/icons/awesome/index.htm
	static std::string makeIconText(const char *icon, const char *join, const char *text)
	{
		char buf[80] = { 0 }; sprintf(buf, "%s%s%s", icon, join, text);
		return buf;
	}
}

#define NB_ICON_TEXT(icon, text)	makeIconText(icon, "\t", text).data()
#define NB_ALIGN_TEXT(text)			makeIconText("\t", "\t", text).data()
#define NB_ICON(icon)				makeIconText(icon, "", "").data()