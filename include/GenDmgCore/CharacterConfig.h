#ifndef _CHARACTER_CONFIG_H
#define _CHARACTER_CONFIG_H
#include "CoreDefine.h"

#include "CharacterLvProp.h"
#include <vector>
#include <functional>

class CharacterConfig
{
public:
	DLL_EXPORT CharacterConfig();
	DLL_EXPORT ~CharacterConfig();
	DLL_EXPORT int getId() const;
	DLL_EXPORT void setId(int val);

	DLL_EXPORT int getLv() const;
	DLL_EXPORT void setLv(int val);

	DLL_EXPORT int getALv() const;
	DLL_EXPORT void setALv(int val);

	DLL_EXPORT int getELv() const;
	DLL_EXPORT void setELv(int val);

	DLL_EXPORT int getQLv() const;
	DLL_EXPORT void setQLv(int val);

	DLL_EXPORT void setIsBreak(bool v);
	DLL_EXPORT bool getIsBreak()const;

	DLL_EXPORT bool getIsFront() const;
	DLL_EXPORT void setIsFront(bool val);



	DLL_EXPORT void reset();

	DLL_EXPORT int getHp() const;
	DLL_EXPORT int getAtk() const;
	DLL_EXPORT int getDef() const;
	DLL_EXPORT SpecialPropType getSpecialPropType()const;
	DLL_EXPORT double getSpecialPropVal()const;

private:
	int getPrevLvPropIndex(bool& isPerfectMatch) const;
	void getRelatedProp(CharacterLvProp& prevPrep, CharacterLvProp& nextPrep) const;
	int getAverageVal(std::function<int(CharacterLvProp& prop)> getValFunc )const;
private:
	int id_= 0;
	int lv_ = 0;
	int aLv_ = 0;
	int eLv_ = 0;
	int qLv_ = 0;
	bool isFront_ = false;
	bool isBreak_ = true;

	std::vector<CharacterLvProp> lvProps_;

};


#endif