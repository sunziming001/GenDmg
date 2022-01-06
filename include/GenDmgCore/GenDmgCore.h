#ifndef GEN_DMG_CORE_H
#define GEN_DMG_CORE_H

#include "CoreDefine.h"
#include <vector>
#include "CharacterBrief.h"
#include "CharacterLvProp.h"
#include "CharacterGrowRate.h"

class GenDmgCore
{
public:
	DLL_EXPORT static GenDmgCore* getInstance();
	DLL_EXPORT void init();
	DLL_EXPORT void uninit();
	DLL_EXPORT std::vector<CharacterBrief> getAllCharacterBrief();
	DLL_EXPORT std::vector<CharacterLvProp> getCharacterLvProps(int charId);
	DLL_EXPORT bool updateCharacterLvProps(int charId, std::vector<CharacterLvProp> props);

	DLL_EXPORT CharacterBrief selectCharacterBrief(int charId,bool& isOk);
	DLL_EXPORT void updateCharacterBreif(const CharacterBrief& brief);

	DLL_EXPORT std::vector<CharacterGrowRate> selectAllGrowRate();
	DLL_EXPORT void insertGrowRate(CharacterGrowRate& rate);
	DLL_EXPORT void updateGrowRate(CharacterGrowRate& rate);
	~GenDmgCore();
private:
	GenDmgCore();
	void testInsert();
	void testCalc();
private:
	static GenDmgCore* instance;

};

#endif