#ifndef CHARACTER_BRIEF_H
#define CHARACTER_BRIEF_H

#include <string>
#include <set>
#include "DamageCell.h"

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

struct CharacterLvProp
{
	bool isBreak=false;
	int lv=1;
	int hp=0;
	int def=0;
	int atk=0;
	SpecialPropType spPropType = SpecialPropType::None;
	double spPropValue = 0.0;

	CharacterLvProp() {}

	CharacterLvProp(int lv, bool isBreak, int hp, int atk, int def,SpecialPropType type, double value)
		:isBreak(isBreak)
		,lv(lv)
		,hp(hp)
		,def(def)
		,atk(atk)
		,spPropType(type)
		,spPropValue(value)
	{

	}
	bool operator<(const CharacterLvProp& prop) const{
		if (lv == prop.lv)
		{
			return !isBreak;
		}
		else {
			return lv < prop.lv;
		}
	}
};


class CharacterBrief
{
public:
	CharacterBrief();
	~CharacterBrief();
	int getId() const;
	void setId(int val);
	std::string getName() const; 
	void setName(const std::string& val);
	std::string getImgPath() const; 
	void setImgPath(const std::string& val);
	void insertLvProp(const CharacterLvProp& prop);
	CharacterLvProp getLvProp(int lv, bool isBreak, bool& hasProp);
	std::set<CharacterLvProp> getLvProps()const;
	DamageType getDmgType() const;
	void setDmgType(DamageType val);
private:
	int id_;
	std::string name_;
	std::string imgPath_;
	std::set<CharacterLvProp> lvProps_;
	DamageType dmgType_;
};


#endif