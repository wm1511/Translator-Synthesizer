#pragma once
#include <thread>
#include <future>
#include "Dictionary.h"
#include "Text.h"
#include "../misc/Config.h"

namespace translator
{
	class Holder
	{
		std::vector<Dictionary> _dicts;

	protected:
		Config _config;
		Text _text;

	public:
		void checkConfigExc();
		void updatePathsFile(std::string& dicts, std::string& out);
		void updatePathsField(std::string& dicts, std::string& out);
		void loadPathsFromFile();
		std::thread loadDicts();
		Dictionary& getDict(int idx);
	};
}