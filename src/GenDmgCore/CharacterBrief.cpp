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


DamageType CharacterBrief::getDmgType() const
{
	return dmgType_;
}

void CharacterBrief::setDmgType(DamageType val)
{
	dmgType_ = val;
}

std::string CharacterBrief::getLuaPath() const
{
	return luaPath_;
}

void CharacterBrief::setLuaPath(std::string val)
{
	luaPath_ = val;
}
