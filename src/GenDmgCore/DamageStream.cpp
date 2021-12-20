#include "DamageStream.h"
#include "CoreLogger.h"

std::map<int, int> DamageStream::Lv2FusionArg = {
	{1,9},{2,9},{3,10},{4,11},{5,11},{6,12},{7,13},{8,14},{9,16},{10,17},
	{11,19},{12,20},{13,22},{14,24},{15,27},{16,30},{17,32},{18,35},{19,38},{20,40},
	{21,43},{22,46},{23,49},{24,51},{25,54},{26,57},{27,59},{28,61},{29,65},{30,68},
	{31,71},{32,75},{33,78},{34,81},{35,85},{36,88},{37,92},{38,96},{39,100},{40,104},
	{41,108},{42,112},{43,117},{44,122},{45,128},{46,134},{47,141},{48,148},{49,155},{50,162},
	{51,168},{52,175},{53,182},{54,189},{55,199},{56,208},{57,217},{58,226},{59,236},{60,246},
	{61,257},{62,270},{63,283},{64,296},{65,312},{66,326},{67,340},{68,354},{69,368},{70,383},
	{71,397},{72,412},{73,426},{74,439},{75,457},{76,473},{77,490},{78,506},{79,522},{80,539},
	{81,555},{82,571},{83,588},{84,605},{85,627},{86,644},{87,663},{88,682},{89,703},{90,723},
};


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

DamageResultSet DamageStream::getDamage(DamageType type) const
{
	std::map<RelfectType, DamageResult> ret;
	std::set<RelfectType> reflectionSets = getRelatedReflectType(type);

	for (auto iter = reflectionSets.begin();
		iter != reflectionSets.end();
		iter++)
	{
		ret[*iter] = calcRelfectDmg(type, *iter);
	}

	/*double ret = 0.0;
	double atk = 0.0;
	double skillRate = 0.0;
	double addtion = 0.0;
	double resist = 0.0;
	double resistRate = 1.0;
	auto iter = dmgCellGroup_.mapDmgType2Cell.find(type);
	int lvSource = 0;
	int lvTarget = 0;
	double dmg = 0.0;
	double dmgCrit = 0.0;

	if (source_ == nullptr
		|| target_ == nullptr)
	{
		LOG_WARN("DamageStream", "source or target is nil");
		return ret;
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
		
		resistRate = (1 - resist / 2);
	}
	else if (resist >= 0.75)
	{
		resistRate = 1 / (1 + 4 * resist);
	}
	else {
		resistRate = (1 - resist);
	}

	dmg = atk * skillRate * (1 + addtion) * (100 + lvSource) / (200 + lvSource + lvTarget) * resistRate;
	dmgCrit = dmg * (1 + source_->getCirtDmgRate());
	*/
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

double DamageStream::calcReflectRate(RelfectType reflectType, bool& isFusion)const
{
	double ret = 1.0;
	double em = source_->getElementMystery();

	double basicAmp = 0.0;
	double emAmp = 2.78 * em / (1400 + em);

	double basicFusion = 0.0;
	double emFusion = (16 * em) / (em + 2000);
	double fusionArg = Lv2FusionArg[source_->getLv()];

	double addition = 0.0; 

	auto reflectAttitionIter = dmgCellGroup_.mapReflectType2Cell.find(reflectType);
	if (reflectAttitionIter != dmgCellGroup_.mapReflectType2Cell.end())
	{
		addition = reflectAttitionIter->second.additon;
	}

	isFusion = false;

	switch (reflectType)
	{
	case RelfectType::EvaporationFire:
		basicAmp = 1.5;
		ret = basicAmp * (1 + emAmp + addition);
		break;
	case RelfectType::EvaporationWater:
		basicAmp = 2.0;
		ret = basicAmp * (1 + emAmp + addition);
		break;
	case RelfectType::MeltFire:
		basicAmp = 2.0;
		ret = basicAmp * (1 + emAmp + addition);
		break;
	case RelfectType::MeltIce:
		basicAmp = 1.5;
		ret = basicAmp * (1 + emAmp + addition);
		break;

	case RelfectType::Overload:
		isFusion = true;
		basicFusion = 4.0;
		ret = fusionArg * basicFusion * (1 + emFusion + addition);
		break;
	case RelfectType::Electrified:
		isFusion = true;
		basicFusion = 2.4;
		ret = fusionArg * basicFusion * (1 + emFusion + addition);
		break;
	case RelfectType::Superconduction:
		isFusion = true;
		basicFusion = 1.0;
		ret = fusionArg * basicFusion * (1 + emFusion + addition);
		break;
	case RelfectType::IceBreak:
		isFusion = true;
		basicFusion = 3.0;
		ret = fusionArg * basicFusion * (1 + emFusion + addition);
		break;
	case RelfectType::Diffusion:
		isFusion = true;
		basicFusion = 1.2;
		ret = fusionArg * basicFusion * (1 + emFusion + addition);
		break;

	case RelfectType::Crystal:
	case RelfectType::None:
	case RelfectType::Count:
		break;
	default:
		break;
	}

	return ret;
}

double DamageStream::calcResistRate(DamageType type, bool isFusion) const
{
	double resistRate = 1.0;

	double resist = 0.0;
	auto iter = dmgCellGroup_.mapDmgType2Cell.find(type);
	int lvSource = 0;
	int lvTarget = 0;


	if (iter != dmgCellGroup_.mapDmgType2Cell.end())
	{
		resist = iter->second.resist;
	}
	lvSource = source_->getLv();
	lvTarget = target_->getLv();

	resist += target_->getDamageResist(type);

	if (resist <= 0.0)
	{
		resistRate = (1 - resist / 2);
	}
	else if (resist >= 0.75)
	{
		resistRate = 1 / (1 + 4 * resist);
	}
	else {
		resistRate = (1 - resist);
	}

	if (!isFusion)
	{
		resistRate *= (100.0 + lvSource) / (200.0 + lvSource + lvTarget);
	}
	return resistRate;
}

DamageResult DamageStream::calcRelfectDmg(DamageType dmgType, RelfectType reflectType) const
{
	DamageResult ret;
	bool isFusion = false;
	double atk = 0.0;
	double skillRate = 0.0;
	double addtionRate = 1.0;
	double critDmgRate = 0.0;
	double critExpRate = 0.0;
	double resistRate = 0.0;
	double reflectRate = calcReflectRate(reflectType, isFusion);
	DamageType reflectDmgType = getRefelctDmgType(reflectType);
	auto additionIter = dmgCellGroup_.mapDmgType2Cell.find(dmgType);

	if (isFusion)
	{
		resistRate = calcResistRate(reflectDmgType, isFusion);
	}
	else {
		resistRate = calcResistRate(dmgType, isFusion);

		if (additionIter != dmgCellGroup_.mapDmgType2Cell.end())
		{
			addtionRate += additionIter->second.additon;
		}
		addtionRate += source_->getDamageAddition(dmgType);
	}
	

	atk = source_->getAtk();
	critDmgRate = 1 + source_->getCirtDmgRate();
	if (source_->getCritRate() <= 1.0)
	{
		critExpRate = 1 + source_->getCirtDmgRate() * source_->getCritRate();
	}
	else {
		critExpRate = 1 + source_->getCirtDmgRate();
	}
	
	skillRate = dmgCellGroup_.skillRate;


	ret.isFusion = isFusion;
	if (isFusion)
	{
		ret.dmg = reflectRate * resistRate;
		ret.dmgCrit = ret.dmg;
		ret.dmgExp = ret.dmg;
	}
	else {
		ret.dmg = atk * skillRate* addtionRate* reflectRate * resistRate;
		ret.dmgCrit = ret.dmg * critDmgRate;
		ret.dmgExp = ret.dmg * critExpRate;
	}
	return ret;
}

std::set<RelfectType> DamageStream::getRelatedReflectType(DamageType type) const
{
	std::set<RelfectType> ret;
	ret.insert(RelfectType::None);
	switch (type)
	{
	case DamageType::Fire:
		ret.insert(RelfectType::EvaporationFire);
		ret.insert(RelfectType::MeltFire);
		ret.insert(RelfectType::Overload);
		ret.insert(RelfectType::Crystal);
		break;
	case DamageType::Water:
		ret.insert(RelfectType::EvaporationWater);
		ret.insert(RelfectType::Electrified);
		ret.insert(RelfectType::Crystal);
		break;
	case DamageType::Thunder:
		ret.insert(RelfectType::Electrified);
		ret.insert(RelfectType::Overload);
		ret.insert(RelfectType::Superconduction);
		ret.insert(RelfectType::Crystal);
		break;
	case DamageType::Wind:
		ret.insert(RelfectType::Diffusion);
		ret.insert(RelfectType::Overload);
		ret.insert(RelfectType::Superconduction);
		ret.insert(RelfectType::Electrified);
		break;
	case DamageType::Ice:
		ret.insert(RelfectType::Superconduction);
		ret.insert(RelfectType::MeltIce);
		ret.insert(RelfectType::Crystal);
		ret.insert(RelfectType::Frozen);
		break;
	case DamageType::Stone:
		ret.insert(RelfectType::Crystal);
		break;
	case DamageType::Physic:
	case DamageType::Count:
	case DamageType::Wood:
	default:
		break;
	}

	return ret;
}

DamageType DamageStream::getRefelctDmgType(RelfectType reflectType) const
{
	DamageType ret = DamageType::None;
	switch (reflectType)
	{
	case RelfectType::EvaporationFire:
		ret = DamageType::Fire;
		break;
	case RelfectType::EvaporationWater:
		ret = DamageType::Water;
		break;
	case RelfectType::MeltFire:
		ret = DamageType::Fire;
		break;
	case RelfectType::MeltIce:
		ret = DamageType::Ice;
		break;
	case RelfectType::Overload:
		ret = DamageType::Fire;
		break;
	case RelfectType::Electrified:
		ret = DamageType::Thunder;
		break;
	case RelfectType::Superconduction:
		ret = DamageType::Ice;
		break;
	case RelfectType::IceBreak:
		ret = DamageType::Physic;
		break;
	case RelfectType::Frozen:
		ret = DamageType::None;
		break;
	case RelfectType::Diffusion:
		ret = DamageType::Wind;
		break;
	case RelfectType::Crystal:
	case RelfectType::Count:
	case RelfectType::None:
	default:
		break;
	}
	return ret;
}
