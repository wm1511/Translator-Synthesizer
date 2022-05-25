#pragma once
#include "imgui/imgui.h"
#include "input.h"
#include "../logic/Wrapper.h"

namespace translator
{
	struct Attributes
	{
		Wrapper wrapper;
		bool configValid = false;
		std::thread dictsLoader;
		ImVec4 backgroundColor;
	};

	void drawUI(Attributes* attr);
}