#pragma once
#include "../data/Dictionary.h"

namespace translator
{
	class Text
	{
		std::string _text;
	public:
		void lower();
		std::string& getText();
		void setText(const std::string& text);
	};
}

