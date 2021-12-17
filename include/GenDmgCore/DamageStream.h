#ifndef _DAMAGE_STREAM_H
#define _DAMAGE_STREAM_H

#include "ICharacter.h"
#include "DamageCell.h"


class DamageStream
{
public:
	DamageStream(CharacterPtr source, CharacterPtr target);
	~DamageStream();
	void setSource(CharacterPtr source);
	void setTarget(CharacterPtr target);

	double getDamage(DamageType type, bool isCrit=false)const;

	DamageStream& operator<<(const DamageCellGroup& v);
private:
	DamageCellGroup dmgCellGroup_;

	CharacterPtr source_;
	CharacterPtr target_;
};


#endif