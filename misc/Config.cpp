#include "Config.h"

void translator::Config::checkExc()
{
	std::ifstream file("misc/config.cfg");
	if (!file)
		throw noConfigExc("Brak pliku konfiguracyjnego");

	std::string relPath, outPath;
	file >> relPath >> outPath;

	bool dictsPresent = true;
	for (size_t i = 0; i < 4; i++)
		dictsPresent = std::filesystem::exists(std::filesystem::path(relPath) / this->_dictNames[i]) && dictsPresent;

	if (!dictsPresent)
		throw noDictsExc("Brak słowników w katalogu");

	if (!std::filesystem::exists(std::filesystem::path(outPath)))
		throw noOutputExc("Nieprawidłowy folder wyjściowy");

	file.close();
}

const std::filesystem::path& translator::Config::getDictsDir()
{
	return this->_relPath;
}

const std::filesystem::path& translator::Config::getOutputDir()
{
	return this->_outPath;
}

void translator::Config::setDictsDir(const std::filesystem::path& path)
{
	this->_relPath = path;
}

void translator::Config::setOutputDir(const std::filesystem::path& path)
{
	this->_outPath = path;
}

const std::string& translator::noDictsExc::what()
{
	return this->_msg;
}

const std::string& translator::noConfigExc::what()
{
	return this->_msg;
}

const std::string& translator::noOutputExc::what()
{
	return this->_msg;
}
