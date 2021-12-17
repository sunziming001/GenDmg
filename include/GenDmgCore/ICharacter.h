#ifndef _I_CHARACTER_H
#define _I_CHARACTER_H
#include <map>
#include <memory>

#include "DamageCell.h"

class ICharacter
{

public:
	int getAtk() const { return atk_; }
	void setAtk(int val) { atk_ = val; }
	int getHp() const { return hp_; }
	void setHp(int val) { hp_ = val; }
	int getDef() const { return def_; }
	void setDef(int val) { def_ = val; }
	int getElementMystery() const { return elementMystery_; }
	void setElementMystery(int val) { elementMystery_ = val; }
	int getPyhicalPower() const { return pyhicalPower_; }
	void setPyhicalPower(int val) { pyhicalPower_ = val; }
	double getCritRate() const { return critRate_; }
	void setCritRate(double val) { critRate_ = val; }
	double getCirtDmgRate() const { return cirtDmgRate_; }
	void setCirtDmgRate(double val) { cirtDmgRate_ = val; }
	double getHealRate() const { return healRate_; }
	void setHealRate(double val) { healRate_ = val; }
	double getHealedRate() const { return healedRate_; }
	void setHealedRate(double val) { healedRate_ = val; }
	double getChargeEffect() const { return chargeEffect_; }
	void setChargeEffect(double val) { chargeEffect_ = val; }
	double getCoolRate() const { return coolRate_; }
	void setCoolRate(double val) { coolRate_ = val; }
	double getShieldEffect() const { return shieldEffect; }
	void setShieldEffect(double val) { shieldEffect = val; }
	int getLv() const { return lv_; }
	void setLv(int val) { lv_ = val; }

	void setDamageAddtion(DamageType type, double v)
	{
		mapDmgType2Cell_[type].additon = v;
	}

	double getDamageAddition(DamageType type)
	{
		return mapDmgType2Cell_[type].additon;
	}

	void setDamageResist(DamageType type, double v)
	{
		mapDmgType2Cell_[type].resist = v;
	}

	double getDamageResist(DamageType type)
	{
		return mapDmgType2Cell_[type].resist;
	}


private:
	int lv_ = 0;

	int hp_ = 0;
	int atk_ = 0;
	int def_ = 0;
	int elementMystery_ = 0;	///< 元素精通
	int pyhicalPower_ = 0;		///< 体力

	double critRate_ = 0.0;
	double cirtDmgRate_ = 0.0;
	double healRate_ = 0.0;
	double healedRate_ = 0.0;
	double chargeEffect_ = 0.0;
	double coolRate_ = 0.0;
	double shieldEffect = 0.0;

	std::map<DamageType, DamageCell> mapDmgType2Cell_;

};

typedef std::shared_ptr<ICharacter> CharacterPtr;

#endif