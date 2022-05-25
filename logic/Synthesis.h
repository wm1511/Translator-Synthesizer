#pragma once
#include <Python.h>
#include <string>

namespace translator
{
	class Synthesis
	{
	public:
		void runPyScript(const char* file, const int argc, const std::string args[]);
	};
}
