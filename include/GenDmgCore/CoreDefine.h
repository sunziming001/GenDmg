#ifndef _CORE_DEFINE_H
#define _CORE_DEFINE_H


#ifdef MAKE_AS_DLL
#  define DLL_EXPORT __declspec(dllexport)
#else
#  define DLL_EXPORT __declspec(dllimport)
#endif

#define MODULE_NAME "GenDmgCore.dll"

#endif;
