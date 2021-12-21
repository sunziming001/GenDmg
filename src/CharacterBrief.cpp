#include "CharacterBrief.h"

CharacterBrief::CharacterBrief()
	:id_(0)
	,dmgType_(DamageType::None)
{

}

CharacterBrief::~CharacterBrief()
{

}

int CharacterBrief::getId() const
{
	return id_;
}

void CharacterBrief::setId(int val)
{
	id_ = val;
}

std::string CharacterBrief::getName() const
{
	return name_;
}

void CharacterBrief::setName(const std::string& val)
{
	name_ = val;
}

std::string CharacterBrief::getImgPath() const
{
	return imgPath_;
}

void CharacterBrief::setImgPath(const std::string& val)
{
	imgPath_ = val;
}

void CharacterBrief::insertLvProp(const CharacterLvProp& prop)
{
	lvProps_.insert(prop);
}

CharacterLvProp CharacterBrief::getLvProp(int lv, bool isBreak, bool& hasProp)
{
	CharacterLvProp key;
	key.lv = lv;
	key.isBreak = isBreak;
	hasProp = false;
	auto iter = lvProps_.find(key);
	if (iter != lvProps_.end())
	{
		hasProp = true;
		return *iter;
	}
	else {
		
		return key;
	}
}

std::set<CharacterLvProp> CharacterBrief::getLvProps() const
{
	return lvProps_;
}

DamageType CharacterBrief::getDmgType() const
{
	return dmgType_;
}

void CharacterBrief::setDmgType(DamageType val)
{
	dmgType_ = val;
}
