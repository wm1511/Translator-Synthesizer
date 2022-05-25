#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace translator
{
	class Config
	{
		std::filesystem::path _relPath;
		std::filesystem::path _outPath;

	public:
		const std::string _dictNames[4] = {"SGJP.tsv", "PLEN.tsv", "PLFR.tsv", "PLCH.tsv"};

		void checkExc();
		const std::filesystem::path& getDictsDir();
		const std::filesystem::path& getOutputDir();
		void setDictsDir(const std::filesystem::path& path);
		void setOutputDir(const std::filesystem::path& path);
	};

	class noConfigExc : std::exception
	{
		std::string _msg;
	public:
		noConfigExc(const std::string& msg) : _msg(msg) {}
		~noConfigExc() {}
		const std::string& what();
	};

	class noDictsExc : std::exception
	{
		std::string _msg;
	public:
		noDictsExc(const std::string& msg) : _msg(msg) {}
		~noDictsExc() {}
		const std::string& what();
	};
	
	class noOutputExc : std::exception
	{
		std::string _msg;
	public:
		noOutputExc(const std::string& msg) : _msg(msg) {}
		~noOutputExc() {}
		const std::string& what();
	};
}