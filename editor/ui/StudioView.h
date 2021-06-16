#pragma once
#include "ImGuiHelper.h"

namespace studio
{

class StudioView : public ImGuiView
{
public:
	using ImGuiView::ImGuiView;

	virtual void onInit() override;
	virtual void onRender() override;
};

}