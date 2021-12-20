#ifndef DAMAGE_CELL_H
#define DAMAGE_CELL_H



enum class DamageType
{
	None,
	Fire,
	Water,
	Wood,
	Thunder,
	Wind,
	Ice,
	Stone,
	Physic,

	Count,
};

enum class RelfectType
{
	None,

	EvaporationFire,
	EvaporationWater,

	MeltFire,
	MeltIce,

	Overload,
	Electrified,
	Superconduction,
	IceBreak,

	Frozen,

	Diffusion,
	Crystal,

	Count,
};

struct DamageCell
{
	DamageCell()
	{
		resist = 0.0;
		additon = 0.0;
	}


	double resist;
	double additon;
};

struct ReflectCell
{
	ReflectCell()
	{
		additon = 0.0;
	}

	double additon;
};

struct DamageResult
{
	DamageResult()
	{
		isFusion = false;
		dmg = 0.0;
		dmgExp = 0.0;
		dmgCrit = 0.0;
	}
	bool isFusion;
	double dmg;
	double dmgExp;
	double dmgCrit;
};
typedef std::map<RelfectType, DamageResult> DamageResultSet;


struct DamageCellGroup
{
	double skillRate = 0.0;
	std::map<DamageType, DamageCell> mapDmgType2Cell;
	std::map<RelfectType, ReflectCell> mapReflectType2Cell;
};

#endif