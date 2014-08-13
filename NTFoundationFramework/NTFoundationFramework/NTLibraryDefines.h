


#ifndef __NTFoundationFramework__NTLibraryDefines__
#define __NTFoundationFramework__NTLibraryDefines__

#ifdef  _WIN32

#include <Windows.h>
#define NT_LIBRARY_EXPORT __declspec(dllexport)
#define NT_LIBRARY_IMPORT __declspec(dllimport)

#elif defined MAC
#define NT_LIBRARY_EXPORT 
#define NT_LIBRARY_IMPORT 

#elif defined LINUX
#define NT_LIBRARY_EXPORT 
#define NT_LIBRARY_IMPORT 
#endif


#endif