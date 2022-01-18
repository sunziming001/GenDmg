#include "CharacterConfig.h"
#include "GenDmgCore.h"

CharacterConfig::CharacterConfig()
{

}

CharacterConfig::~CharacterConfig()
{

}

int CharacterConfig::getId() const
{
	return id_;
}

void CharacterConfig::setId(int val)
{
	if (id_ != val)
	{
		id_ = val;
		reset();
	}

}

int CharacterConfig::getLv() const
{
	return lv_;
}

void CharacterConfig::setLv(int val)
{
	lv_ = val;
}

int CharacterConfig::getALv() const
{
	return aLv_;
}

void CharacterConfig::setALv(int val)
{
	aLv_ = val;
}

int CharacterConfig::getELv() const
{
	return eLv_;
}

void CharacterConfig::setELv(int val)
{
	eLv_ = val;
}


int CharacterConfig::getQLv() const
{
	return qLv_;
}

void CharacterConfig::setQLv(int val)
{
	qLv_ = val;
}

void CharacterConfig::setIsBreak(bool v)
{
	isBreak_ = v;
}

bool CharacterConfig::getIsBreak() const
{
	return isBreak_;
}

bool CharacterConfig::getIsFront() const
{
	return isFront_;
}

void CharacterConfig::setIsFront(bool val)
{
	isFront_ = val;
}

void CharacterConfig::reset()
{
	lvProps_ = GenDmgCore::getInstance()->getCharacterLvProps(getId());
}

int CharacterConfig::getHp() const
{
	return getAverageVal([](const CharacterLvProp& prop)->int {
		return prop.getHp();
	});
}

int CharacterConfig::getAtk() const
{
	return getAverageVal([](const CharacterLvProp& prop)->int {
		return prop.getAtk();
	});
}

int CharacterConfig::getDef() const
{
	return getAverageVal([](const CharacterLvProp& prop)->int {
		return prop.getDef();
	});
}

SpecialPropType CharacterConfig::getSpecialPropType() const
{
	SpecialPropType ret = SpecialPropType::None;


	return ret;
}

double CharacterConfig::getSpecialPropVal() const
{
	double ret = 0.0;

	return ret;
}

int CharacterConfig::getPrevLvPropIndex(bool& isPerfectMatch) const
{
	int index = 0;
	for (int i = 0;  i < lvProps_.size(); i++)
	{
		const CharacterLvProp& curProp = lvProps_[i];
		if (curProp.getLv() > getLv())
		{
			index = i - 1;
			break;
		}
		else if (curProp.getLv() == getLv()
			&& curProp.getIsBreak() == getIsBreak())
		{
			isPerfectMatch = true;
			index = i;
			break;
		}
	}

	if (index < 0)
		index = 0;


	return index;
}

void CharacterConfig::getRelatedProp(CharacterLvProp& prevPrep, CharacterLvProp& nextPrep) const
{
	bool isPrefectMatch = false;
	int prevIndx = getPrevLvPropIndex(isPrefectMatch);
	int nextIndx = prevIndx + 1;

	if (nextIndx >= lvProps_.size() || isPrefectMatch)
		nextIndx = prevIndx;



	prevPrep = lvProps_[prevIndx];
	nextPrep = lvProps_[nextIndx];
}

int CharacterConfig::getAverageVal(std::function<int(CharacterLvProp& prop)> getValFunc)const
{
	int ret = 0;
	CharacterLvProp prevProp;
	CharacterLvProp nextProp;

	getRelatedProp(prevProp, nextProp);
	int dv = (getValFunc(nextProp) - getValFunc(prevProp));
	int dlv = (nextProp.getLv() - prevProp.getLv());
	int lvCnt = getLv() - prevProp.getLv();
	if (dlv != 0)
	{
		dv = dv / dlv;
	}

	ret = getValFunc(prevProp) + dv * lvCnt;
	return ret;
}
