#pragma once
#include <regex>
#include "../data/Text.h"

namespace translator
{
	class Translation
	{
	public:
		void translate(Dictionary& dict, Text& text);
	};
}

