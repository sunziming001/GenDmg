#ifndef GEN_DMG_CORE_H
#define GEN_DMG_CORE_H

#ifdef MAKE_AS_DLL
#  define DLL_EXPORT __declspec(dllexport)
#else
#  define DLL_EXPORT __declspec(dllimport)
#endif


class GenDmgCore
{
public:
	DLL_EXPORT static GenDmgCore* getInstance();
	DLL_EXPORT void init();
	DLL_EXPORT void uninit();

	~GenDmgCore();
private:
	GenDmgCore();
private:
	static GenDmgCore* instance;

};

#endif