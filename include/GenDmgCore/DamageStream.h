#ifndef _DAMAGE_STREAM_H
#define _DAMAGE_STREAM_H

#include "ICharacter.h"
#include "DamageCell.h"
#include <set>

class DamageStream
{
public:
	DamageStream(CharacterPtr source, CharacterPtr target);
	~DamageStream();
	void setSource(CharacterPtr source);
	void setTarget(CharacterPtr target);

	DamageResultSet getDamage(DamageType type)const;

	DamageStream& operator<<(const DamageCellGroup& v);
private:
	double calcReflectRate(RelfectType reflectType, bool& isFusion)const;
	double calcResistRate(DamageType type, bool isFusion)const;

	DamageResult calcRelfectDmg(DamageType type, RelfectType reflectType)const;

	std::set<RelfectType> getRelatedReflectType(DamageType type)const;
	DamageType getRefelctDmgType(RelfectType reflectType)const;
private:
	static std::map<int, int> Lv2FusionArg;

	DamageCellGroup dmgCellGroup_;

	CharacterPtr source_;
	CharacterPtr target_;
};


#endif