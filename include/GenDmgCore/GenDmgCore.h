#ifndef GEN_DMG_CORE_H
#define GEN_DMG_CORE_H

#include "CoreDefine.h"
#include <vector>
#include "CharacterBrief.h"
#include "CharacterLvProp.h"
class GenDmgCore
{
public:
	DLL_EXPORT static GenDmgCore* getInstance();
	DLL_EXPORT void init();
	DLL_EXPORT void uninit();
	DLL_EXPORT std::vector<CharacterBrief> getAllCharacterBrief();
	DLL_EXPORT std::vector<CharacterLvProp> getCharacterLvProps(int charId);
	~GenDmgCore();
private:
	GenDmgCore();
	void testInsert();
	void testCalc();
private:
	static GenDmgCore* instance;

};

#endif