#include "DamageStream.h"
#include "CoreLogger.h"

DamageStream::DamageStream(CharacterPtr source, CharacterPtr target)
	: source_(source)
	, target_(target)
{

}

DamageStream::~DamageStream()
{

}

void DamageStream::setSource(CharacterPtr source)
{
	source_ = source;
}

void DamageStream::setTarget(CharacterPtr target)
{
	target_ = target;
}

double DamageStream::getDamage(DamageType type, bool isCrit) const
{
	double ret = 0.0;
	double atk = 0.0;
	double skillRate = 0.0;
	double addtion = 0.0;
	double resist = 0.0;
	auto iter = dmgCellGroup_.mapDmgType2Cell.find(type);
	int lvSource = 0;
	int lvTarget = 0;
	if (source_ == nullptr
		|| target_ == nullptr)
	{
		LOG_WARN("DamageStream", "source or target is nil");
		return 0.0;
	}

	if (iter != dmgCellGroup_.mapDmgType2Cell.end())
	{
		addtion = iter->second.additon;
		resist = iter->second.resist;
	}
	lvSource = source_->getLv();
	lvTarget = target_->getLv();

	atk = source_->getAtk();
	skillRate = dmgCellGroup_.skillRate;
	addtion += source_->getDamageAddition(type);
	resist += target_->getDamageResist(type);
	if (resist <= 0.0)
	{
		resist = resist / 2.0;
	}
	ret = atk * skillRate * (1 + addtion) * (100 + lvSource) / (200 + lvSource + lvTarget) * (1 - resist);
	if (isCrit)
	{
		ret *= 1 + source_->getCirtDmgRate();
	}

	return ret;
}

DamageStream& DamageStream::operator<<(const DamageCellGroup& v)
{
	if (v.skillRate != 0.0 && dmgCellGroup_.skillRate != 0.0)
	{
		LOG_WARN("DamageStream", "SkillRate will be overwrited");
		dmgCellGroup_.skillRate = 0.0;
	}
	dmgCellGroup_.skillRate += v.skillRate;

	for (auto& p : v.mapDmgType2Cell)
	{
		DamageType type = p.first;
		double addtion = 0.0;
		double resist = 0.0;

		const std::map<DamageType, DamageCell>& valMap = v.mapDmgType2Cell;
		auto cellIter = valMap.find(type);
		if (cellIter != valMap.end())
		{
			addtion = cellIter->second.additon;
			resist = cellIter->second.resist;
		}

		dmgCellGroup_.mapDmgType2Cell[type].additon += p.second.additon;
		dmgCellGroup_.mapDmgType2Cell[type].resist += p.second.resist;
	}

	return *this;
}
