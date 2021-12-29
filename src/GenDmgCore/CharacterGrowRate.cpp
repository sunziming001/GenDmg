#include "CharacterGrowRate.h"

CharacterGrowRate::CharacterGrowRate()
{

}

CharacterGrowRate::~CharacterGrowRate()
{

}

bool CharacterGrowRate::operator<(const CharacterGrowRate& prop) const
{
	return getId() < prop.getId();
}

int CharacterGrowRate::getId() const
{
	return id_;
}

void CharacterGrowRate::setId(int val)
{
	id_ = val;
}

std::string CharacterGrowRate::getName() const
{
	return name_;
}

void CharacterGrowRate::setName(std::string val)
{
	name_ = val;
}

void CharacterGrowRate::setLvRate(int lv, double rate)
{
	mapLv2Rate_[lv] = rate;
}

double CharacterGrowRate::getLvRate(int lv, bool* isOk /*= nullptr*/) const
{
	double ret = 0.0;
	bool hasFound = false;
	auto iter = mapLv2Rate_.find(lv);
	if (iter != mapLv2Rate_.end())
	{
		ret = iter->second;
		hasFound = true;
	}

	if (isOk)
	{
		*isOk = hasFound;
	}

	return ret;
}
