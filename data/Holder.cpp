#include "Holder.h"

std::thread translator::Holder::loadDicts()
{

	for (size_t i = 0; i < 4; i++)
		this->_dicts.push_back(Dictionary());
	
	std::thread gramLoader([this]
		{
			this->_dicts[0].loadDict( this->_config.getDictsDir() / this->_config._dictNames[0]);
		});

	for (size_t i = 1; i < _dicts.size(); i++)
		std::future<void> tmp = std::async(std::launch::async, &Dictionary::loadDict,
			&this->_dicts[i], this->_config.getDictsDir() / this->_config._dictNames[i]);

	return gramLoader;
}

translator::Dictionary& translator::Holder::getDict(int idx)
{
	return _dicts[idx];
}

void translator::Holder::updatePathsFile(std::string& dicts, std::string& out)
{
	std::ofstream file("misc/config.cfg");
	file << dicts << '\n' << out;
	file.close();
}

void translator::Holder::updatePathsField(std::string& dicts, std::string& out)
{
	this->_config.setDictsDir(std::filesystem::path(dicts));
	this->_config.setOutputDir(std::filesystem::path(out));
}

void translator::Holder::loadPathsFromFile()
{
	std::ifstream file("misc/config.cfg");
	std::string dicts, out;
	file >> dicts >> out;
	this->_config.setDictsDir(std::filesystem::path(dicts));
	this->_config.setOutputDir(std::filesystem::path(out));
}

void translator::Holder::checkConfigExc()
{
	this->_config.checkExc();
}