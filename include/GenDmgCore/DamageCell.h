#ifndef DAMAGE_CELL_H
#define DAMAGE_CELL_H



enum class DamageType
{
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


struct DamageCellGroup
{
	double skillRate = 0.0;
	std::map<DamageType, DamageCell> mapDmgType2Cell;
};

#endif