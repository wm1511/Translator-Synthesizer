#pragma once
#include "Translation.h"
#include "Synthesis.h"
#include "../data/Holder.h"

namespace translator
{
	class Wrapper : public Holder
	{
		Synthesis _synthesizer;
		Translation _translator;

		std::string indexToID(size_t idx);

	public:
		bool configurate(std::string& dicts, std::string& out, std::string& message);
		void translate(std::string& src, std::string& dest, Dictionary& langDict, Dictionary& gramDict);
		void synthesizeIn(std::string text, int rate, int idx);
		void synthesizeOut(std::string text, int rate, int idx, std::string filename);
	};
}