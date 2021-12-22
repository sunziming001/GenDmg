#ifndef _CHARACTER_LV_PROP_H
#define _CHARACTER_LV_PROP_H
#include "CoreDefine.h"

enum class SpecialPropType
{
	None,
	AtkPercent,
	DefPercent,
	HpPercent,
	CritRate,
	CritDmgRate,
	ChargeEffect,
	FireAdditon,
	WaterAddition,
	WookAddition,
	ThunderAddition,
	WindAddition,
	IceAddition,
	StoneAddition,
	PhysicAddition,
	HealRate,
};


class CharacterLvProp
{
public:
	DLL_EXPORT CharacterLvProp(); 
	DLL_EXPORT ~CharacterLvProp();
	DLL_EXPORT CharacterLvProp(int lv, bool isBreak, int hp, int atk, int def, SpecialPropType type, double value);
	DLL_EXPORT bool operator<(const CharacterLvProp& prop) const;

	DLL_EXPORT bool getIsBreak() const;
	DLL_EXPORT void setIsBreak(bool val);
	DLL_EXPORT int getLv() const;
	DLL_EXPORT void setLv(int val);
	DLL_EXPORT int getDef() const;
	DLL_EXPORT void setDef(int val);
	DLL_EXPORT int getAtk() const;
	DLL_EXPORT void setAtk(int val);
	DLL_EXPORT SpecialPropType getSpPropType() const;
	DLL_EXPORT void setSpPropType(SpecialPropType val);
	DLL_EXPORT double getSpPropValue() const;
	DLL_EXPORT void setSpPropValue(double val);

	DLL_EXPORT int getHp() const;
	DLL_EXPORT void setHp(int val);
private:
	bool isBreak_ = false;
	int lv_ = 1;
	int hp_ = 0;
	int def_ = 0;
	int atk_ = 0;
	SpecialPropType spPropType_ = SpecialPropType::None;
	double spPropValue_ = 0.0;
};




#endif;