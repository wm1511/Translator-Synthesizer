#include "Wrapper.h"

std::string translator::Wrapper::indexToID(size_t idx)
{
	if (idx == 0)
		return "1";
	else if (idx == 1)
		return "2";
	else if (idx == 2)
		return "4";
	else
		return "0";
}

bool translator::Wrapper::configurate(std::string& dicts, std::string& out, std::string& message)
{
	try
	{
		this->checkConfigExc();
		this->updatePathsField(dicts, out);
		return true;
	}
	catch (noConfigExc& e)
	{
		this->updatePathsFile(dicts, out);
		message = e.what();
		return false;
	}
	catch (noDictsExc& e)
	{
		this->updatePathsFile(dicts, out);
		message = e.what();
		return false;
	}
	catch (noOutputExc& e)
	{
		this->updatePathsFile(dicts, out);
		message = e.what();
		return false;
	}
}

void translator::Wrapper::translate(std::string& src, std::string& dest, Dictionary& gramDict, Dictionary& langDict)
{
	this->_text.setText(src);
	this->_translator.translate(gramDict, this->_text);
	this->_translator.translate(langDict, this->_text);
	dest = this->_text.getText();
}

void translator::Wrapper::synthesizeIn(std::string text, int rate, int idx)
{
	const char* file = "python/synthesize_locally.py";
	const int argc = 3;
	std::string argv[argc] = 
	{ 
		text, 
		std::to_string(rate), 
		this->indexToID(idx)
	};
	this->_synthesizer.runPyScript(file, argc, argv);
}

void translator::Wrapper::synthesizeOut(std::string text, int rate, int idx, std::string filename)
{
	const char* file = "python/synthesize_to_file.py";
	const int argc = 4;
	std::string argv[argc] = 
	{ 
		text, 
		std::to_string(rate), 
		this->indexToID(idx), 
		(this->_config.getOutputDir() / filename).generic_string() + ".wav"
	};
	this->_synthesizer.runPyScript(file, argc, argv);
}
