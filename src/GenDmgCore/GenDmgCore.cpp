#include "GenDmgCore.h"
#include "CoreLogger.h"
#include "ICharacter.h"
#include "DamageStream.h"

GenDmgCore* GenDmgCore::getInstance()
{
	if (instance == nullptr)
		instance = new GenDmgCore;

	return instance;
}

void GenDmgCore::init()
{
	LOG_INIT(0);
	LOG_INFO("GenDmgCore", "init.");

	DamageCellGroup skill;
	DamageCellGroup weapon;
	DamageCellGroup reduceResist;
	CharacterPtr pPlayer = std::make_shared<ICharacter>();
	CharacterPtr pTarget = std::make_shared<ICharacter>();
	DamageStream ds(pPlayer, pTarget);

	pPlayer->setAtk(1285);
	pPlayer->setLv(81);
	pPlayer->setElementMystery(361);
	pPlayer->setCirtDmgRate(0.92);
	pPlayer->setDamageAddtion(DamageType::Fire, 0.616);

	pTarget->setLv(92);
	pTarget->setDamageResist(DamageType::Fire, 0.1);


	skill.skillRate = 1.89;

	weapon.mapDmgType2Cell[DamageType::Fire].additon = 0.28;

	reduceResist.mapDmgType2Cell[DamageType::Fire].resist = -0.15;
	
	ds << skill << weapon << reduceResist;

	DamageResultSet set = ds.getDamage(DamageType::Fire);

}

void GenDmgCore::uninit()
{
	LOG_INFO("GenDmgCore", "uninit.");
}

GenDmgCore::~GenDmgCore()
{

}

GenDmgCore::GenDmgCore()
{

}

GenDmgCore* GenDmgCore::instance=nullptr;

