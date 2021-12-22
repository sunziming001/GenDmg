#include "CharacterLvProp.h"

CharacterLvProp::CharacterLvProp(int lv, bool isBreak, int hp, int atk, int def, SpecialPropType type, double value)
	:isBreak_(isBreak)
	, lv_(lv)
	, hp_(hp)
	, def_(def)
	, atk_(atk)
	, spPropType_(type)
	, spPropValue_(value)
{

}

CharacterLvProp::CharacterLvProp()
{

}

CharacterLvProp::~CharacterLvProp()
{

}

bool CharacterLvProp::operator<(const CharacterLvProp& prop) const
{
	if (getLv() == prop.getLv())
	{
		return !getIsBreak();
	}
	else {
		return getLv() < prop.getLv();
	}
}

bool CharacterLvProp::getIsBreak() const
{
	return isBreak_;
}

void CharacterLvProp::setIsBreak(bool val)
{
	isBreak_ = val;
}

int CharacterLvProp::getLv() const
{
	return lv_;
}

void CharacterLvProp::setLv(int val)
{
	lv_ = val;
}

int CharacterLvProp::getDef() const
{
	return def_;
}

void CharacterLvProp::setDef(int val)
{
	def_ = val;
}

int CharacterLvProp::getAtk() const
{
	return atk_;
}

void CharacterLvProp::setAtk(int val)
{
	atk_ = val;
}

SpecialPropType CharacterLvProp::getSpPropType() const
{
	return spPropType_;
}
void CharacterLvProp::setSpPropType(SpecialPropType val)
{
	spPropType_ = val;
}

double CharacterLvProp::getSpPropValue() const
{
	return spPropValue_;
}

void CharacterLvProp::setSpPropValue(double val)
{
	spPropValue_ = val;
}

int CharacterLvProp::getHp() const
{
	return hp_;
}


void CharacterLvProp::setHp(int val)
{
	hp_ = val;
}