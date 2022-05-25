#pragma once
#define __STDC_WANT_LIB_EXT1__ 1
#include <cstring>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace translator
{
	class Dictionary
	{
		std::unordered_map<std::string, std::string> _dict;

	public:
		void loadDict(const std::filesystem::path& path);
		const std::string getEquivalent(const std::string& word);
		size_t getSize();
	};
}