


#ifndef __NTFoundationFramework__NTLibraryDefines__
#define __NTFoundationFramework__NTLibraryDefines__

#ifdef  _WIN32

#include <Windows.h>
#define NT_LIBRARY_EXPORT __declspec(dllexport)
#define NT_LIBRARY_IMPORT __declspec(dllimport)

#elif defined __APPLE__
#define NT_LIBRARY_EXPORT __attribute__ ((visibility ("default")))
#define NT_LIBRARY_IMPORT __attribute__ ((visibility ("default")))

#elif defined LINUX
#define NT_LIBRARY_EXPORT 
#define NT_LIBRARY_IMPORT 
#endif


#endif