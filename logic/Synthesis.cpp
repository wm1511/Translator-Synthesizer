#include "Synthesis.h"

void translator::Synthesis::runPyScript(const char* file, const int argc, const std::string argv[])
{
    FILE* fp;

    wchar_t** wargv = new wchar_t* [argc];

    for (int i = 0; i < argc; i++)
        wargv[i] = Py_DecodeLocale(argv[i].c_str(), nullptr);
        
    Py_SetProgramName(wargv[0]);
    Py_Initialize();
    PySys_SetArgv(argc, wargv);
    fp = _Py_fopen(file, "r");
    PyRun_SimpleFile(fp, file);
    Py_Finalize();

    for (int i = 0; i < argc; i++)
    {
        PyMem_RawFree(wargv[i]);
        wargv[i] = nullptr;
    }

    delete[] wargv;
    wargv = nullptr;
}