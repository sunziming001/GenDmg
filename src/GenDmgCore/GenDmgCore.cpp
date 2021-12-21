#include "GenDmgCore.h"
#include "CoreLogger.h"
#include "ICharacter.h"
#include "DamageStream.h"
#include "DBHelper.h"

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
	DBHelper::getInstance()->init();
	DBHelper::getInstance()->selectAllCharacterBrief();
}

void GenDmgCore::uninit()
{
	LOG_INFO("GenDmgCore", "uninit.");
	DBHelper::getInstance()->uninit();

}

GenDmgCore::~GenDmgCore()
{

}

GenDmgCore::GenDmgCore()
{

}

void GenDmgCore::testInsert()
{
	CharacterBrief brief;
	brief.setName("Mona");
	brief.setImgPath("/res/char/mona.png");
	brief.setDmgType(DamageType::Water);

	brief.insertLvProp(CharacterLvProp(1, true, 810, 51, 22, SpecialPropType::ChargeEffect, 0.0));
	brief.insertLvProp(CharacterLvProp(20, false, 2102, 58, 132, SpecialPropType::ChargeEffect, 0.0));
	brief.insertLvProp(CharacterLvProp(20, true, 2797, 77, 176, SpecialPropType::ChargeEffect, 0.0));
	brief.insertLvProp(CharacterLvProp(40, false, 4185, 115, 263, SpecialPropType::ChargeEffect, 0.0));
	brief.insertLvProp(CharacterLvProp(40, true, 4678, 129, 294, SpecialPropType::ChargeEffect, 8.0));
	brief.insertLvProp(CharacterLvProp(50, false, 5383, 148, 338, SpecialPropType::ChargeEffect, 8.0));
	brief.insertLvProp(CharacterLvProp(50, true, 6041, 167, 379, SpecialPropType::ChargeEffect, 16.0));
	brief.insertLvProp(CharacterLvProp(60, false, 6752, 186, 424, SpecialPropType::ChargeEffect, 16.0));
	brief.insertLvProp(CharacterLvProp(60, true, 7246, 200, 455, SpecialPropType::ChargeEffect, 16.0));
	brief.insertLvProp(CharacterLvProp(70, false, 7964, 220, 500, SpecialPropType::ChargeEffect, 16.0));
	brief.insertLvProp(CharacterLvProp(70, true, 8458, 233, 531, SpecialPropType::ChargeEffect, 24.0));
	brief.insertLvProp(CharacterLvProp(80, false, 9184, 253, 576, SpecialPropType::ChargeEffect, 24.0));
	brief.insertLvProp(CharacterLvProp(80, true, 9677, 267, 607, SpecialPropType::ChargeEffect, 32.0));
	brief.insertLvProp(CharacterLvProp(90, false, 10409, 287, 653, SpecialPropType::ChargeEffect, 32.0));

	DBHelper::getInstance()->insertCharacterBrief(brief);
}

void GenDmgCore::testCalc()
{
	DamageCellGroup skill;
	DamageCellGroup weapon;
	DamageCellGroup reduceResist;
	CharacterPtr pPlayer = std::make_shared<ICharacter>();
	CharacterPtr pTarget = std::make_shared<ICharacter>();
	DamageStream ds(pPlayer, pTarget);

	pPlayer->setAtk(1285);
	pPlayer->setLv(89);
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

GenDmgCore* GenDmgCore::instance=nullptr;

