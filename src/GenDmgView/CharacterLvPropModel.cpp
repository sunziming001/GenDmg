#include "CharacterLvPropModel.h"

CharacterLvPropModel::CharacterLvPropModel(int charId, QObject* parent /*= nullptr*/)
	:QAbstractTableModel(parent)
	, charId_(charId)
{
	lvProps_ = GenDmgCore::getInstance()->getCharacterLvProps(charId);
}

CharacterLvPropModel::~CharacterLvPropModel()
{

}

int CharacterLvPropModel::rowCount(const QModelIndex&) const
{
	return CharacterLvPropModel::RowCnt;
}

int CharacterLvPropModel::columnCount(const QModelIndex&) const
{
	return CharacterLvPropModel::ColCnt;
}

QVariant CharacterLvPropModel::data(const QModelIndex& index, int role /*= Qt::DisplayRole*/) const
{
	QVariant value;
	switch (role)
	{
	case Qt::EditRole:
		value = getEditData(index);
		break;
	case Qt::DisplayRole:
		value = getDisplayData(index);
		break;
	}

	return value;
}

Qt::ItemFlags CharacterLvPropModel::flags(const QModelIndex& index) const
{
	Qt::ItemFlags ret = QAbstractTableModel::flags(index);
	if (isSpecialPropIndex(index)
		|| isIntIndex(index)
		|| isDoubleIndex(index))
	{
		ret |= Qt::ItemIsEditable;
	}

	return ret;
}

QString CharacterLvPropModel::specialPropTypeToString(SpecialPropType type)
{
	QString ret;
	switch (type)
	{
	case SpecialPropType::AtkPercent:
		ret = tr("AtkPercent");
		break;
	case SpecialPropType::DefPercent:
		ret = tr("DefPercent");
		break;
	case SpecialPropType::HpPercent:
		ret = tr("HpPercent");
		break;
	case SpecialPropType::CritRate:
		ret = tr("CritRate");
		break;
	case SpecialPropType::CritDmgRate:
		ret = tr("CritDmgRate");
		break;
	case SpecialPropType::ChargeEffect:
		ret = tr("ChargeEffect");
		break;
	case SpecialPropType::FireAdditon:
		ret = tr("FireAdditon");
		break;
	case SpecialPropType::WaterAddition:
		ret = tr("WaterAddition");
		break;
	case SpecialPropType::WookAddition:
		ret = tr("WookAddition");;
		break;
	case SpecialPropType::ThunderAddition:
		ret = tr("ThunderAddition");
		break;
	case SpecialPropType::WindAddition:
		ret = tr("WindAddition");
		break;
	case SpecialPropType::IceAddition:
		ret = tr("IceAddition");
		break;
	case SpecialPropType::StoneAddition:
		ret = tr("StoneAddition");
		break;
	case SpecialPropType::PhysicAddition:
		ret = tr("PhysicAddition");
		break;
	case SpecialPropType::HealRate:
		ret = tr("HealRate");
		break;
	default:
		break;
	}
	return ret;
}

bool CharacterLvPropModel::isSpecialPropIndex(const QModelIndex& index)
{

	return index.row() == 0 && index.column() == 7;
}

bool CharacterLvPropModel::isIntIndex(const QModelIndex& index)
{
	int lv = getIndexLv(index);
	bool isBreak = isIndexBreak(index);
	if (lv == 1 && isBreak == false)
	{
		return false;
	}
	else if (lv == 90 && isBreak == true)
	{
		return false;
	}
	else {
		return index.row() >= 2 && index.column() <= 6 && index.column() >= 1;
	}
	
}

bool CharacterLvPropModel::isDoubleIndex(const QModelIndex& index)
{
	int lv = getIndexLv(index);
	bool isBreak = isIndexBreak(index);
	if (lv == 1 && isBreak == false)
	{
		return false;
	}
	else if (lv == 90 && isBreak == true)
	{
		return false;
	}
	else {
		return index.row() >= 2 && index.column() >= 7;
	}
}

bool CharacterLvPropModel::isDefIndex(const QModelIndex& index)
{
	return index.row() >= 2 && (index.column() == 5 || index.column() == 6);
}

bool CharacterLvPropModel::isAtkIndex(const QModelIndex& index)
{
	return index.row() >= 2 && (index.column() == 3 || index.column() == 4);
}

bool CharacterLvPropModel::isHpIndex(const QModelIndex& index)
{
	return index.row() >= 2 && (index.column() == 1|| index.column() == 2);
}

bool CharacterLvPropModel::isSpecialPropValIndex(const QModelIndex& index)
{
	return index.row() >= 2 && (index.column() == 7 || index.column() == 8);
}

int CharacterLvPropModel::getIndexLv(const QModelIndex& index)
{
	int ret = 0;
	switch (index.row())
	{
	case 2:
		ret = 1;
		break;
	case 3:
		ret = 20;
		break;
	case 4:
		ret = 40;
		break;
	case 5:
		ret = 50;
		break;
	case 6:
		ret = 60;
		break;
	case 7:
		ret = 70;
		break;
	case 8:
		ret = 80;
		break;
	case 9:
		ret = 90;
		break;
	}
	return ret;
}

bool CharacterLvPropModel::isIndexBreak(const QModelIndex& index)
{
	return index.column() %2 == 0;
}

bool CharacterLvPropModel::setData(const QModelIndex& index, const QVariant& value, int role /*= Qt::EditRole*/)
{
	bool ret = false;
	switch (role)
	{
	case Qt::EditRole:
		ret = setEditData(index,value);
		break;
	default:
		ret = QAbstractTableModel::setData(index, value, role);
		break;
	} 

	return ret;
}

void CharacterLvPropModel::resetCharacterId(int charId)
{
	charId_ = charId;
	lvProps_ = GenDmgCore::getInstance()->getCharacterLvProps(charId);
	QModelIndex topLeft = createIndex(0, 0);
	QModelIndex bottomRight = createIndex(RowCnt-1, ColCnt-1);
	dataChanged(topLeft, bottomRight);
}

void CharacterLvPropModel::saveToDB()
{
	GenDmgCore::getInstance()->updateCharacterLvProps(charId_, lvProps_);
}

void CharacterLvPropModel::resetFromDB()
{
	resetCharacterId(charId_);
}

QVariant CharacterLvPropModel::getDisplayData(const QModelIndex& index) const
{
	QVariant ret = "--";
	if (index.row() == 0 && index.column() == 0)
	{
		ret = tr("level");
	}
	else if (index.row() == 0 && index.column() == 1)
	{
		ret = tr("max hp");
	}
	else if (index.row() == 0 && index.column() == 3)
	{
		ret = tr("max atk");
	}
	else if (index.row() == 0 && index.column() == 5)
	{
		ret = tr("max def");
	}
	else if (isSpecialPropIndex(index))
	{
		ret = getSpecialPropName();
	}
	else if (index.row() == 1 && index.column() != 0)
	{
		if (index.column() % 2 == 0)
		{
			ret = tr("aft break");
		}
		else {
			ret = tr("bef break"); 
		}
	}
	else if (index.column() == 0)
	{
		ret =QString::number(getIndexLv(index)) ;
	}
	else {
		ret = getLvPropString(index);
	}

	return ret;
}

QVariant CharacterLvPropModel::getEditData(const QModelIndex& index) const
{
	QVariant ret;
	if (lvProps_.empty())
	{
		return ret;
	}

	if (isSpecialPropIndex(index))
	{
		ret =static_cast<int>(lvProps_[0].getSpPropType());
	}
	else if(isIntIndex(index) || isDoubleIndex(index)) {
		ret = getLvPropEditData(index);
	}
	return ret;
}




bool CharacterLvPropModel::setEditData(const QModelIndex& index, const QVariant& value)
{
	bool ret = false;

	if (isSpecialPropIndex(index))
	{
		SpecialPropType type = static_cast<SpecialPropType>(value.toInt());
		QString txt = specialPropTypeToString(type);

		for (auto& prop : lvProps_)
		{
			prop.setSpPropType(type);
		}
		ret = true;
	}
	else if (isIntIndex(index) || isDoubleIndex(index))
	{
		bool isOk = false;
		setLvPropVarient(index, value);
		CharacterLvProp prop = getLvProp(index, isOk);
		
		ret = true;
	}
	else 
	{

	}


	if (ret)
	{
		emit dataChanged(index, index);
	}
	return ret;
}

QString CharacterLvPropModel::getSpecialPropName() const
{
	QString ret = "--";
	if (lvProps_.size() > 0)
	{
		SpecialPropType type = lvProps_[0].getSpPropType();
		return specialPropTypeToString(type);
	}

	return ret;
}

QString CharacterLvPropModel::getLvPropString(const QModelIndex& index) const
{
	QString ret = "--";
	bool isOk = false;
	const CharacterLvProp& prop = getLvProp(index, isOk);
	if (!isOk)
		return ret;

	if (isDefIndex(index))
	{
		ret = QString::number(prop.getDef());
	}
	else if (isAtkIndex(index))
	{
		ret = QString::number(prop.getAtk());
	}
	else if (isHpIndex(index))
	{
		ret = QString::number(prop.getHp());
	}
	else if (isSpecialPropValIndex(index))
	{
		int precent = prop.getSpPropValue() * 100;
		ret = QString::number(precent)+"%";
	}


	return ret;
}

QVariant CharacterLvPropModel::getLvPropEditData(const QModelIndex& index) const
{
	QVariant ret;
	bool isOk = false;
	const CharacterLvProp& prop = getLvProp(index, isOk);
	if (!isOk)
		return ret;

	if (isDefIndex(index))
	{
		ret = prop.getDef();
	}
	else if (isAtkIndex(index))
	{
		ret = prop.getAtk();
	}
	else if (isHpIndex(index))
	{
		ret = prop.getHp();
	}
	else if (isSpecialPropValIndex(index))
	{
		ret = prop.getSpPropValue();
	}


	return ret;
}

void CharacterLvPropModel::setLvPropVarient(const QModelIndex& index, const QVariant& value)
{
	bool isOk = false;
	CharacterLvProp& prop = getLvProp(index, isOk);
	
	if (isOk)
	{
		if (isDefIndex(index))
		{
			prop.setDef(value.toInt());
		}
		else if (isAtkIndex(index))
		{
			prop.setAtk(value.toInt());
		}
		else if (isHpIndex(index))
		{
			prop.setHp(value.toInt());
		}
		else if (isSpecialPropValIndex(index))
		{
			prop.setSpPropValue(value.toDouble());
		}
	}

}

const CharacterLvProp& CharacterLvPropModel::getLvProp(const QModelIndex& index, bool& isOk) const
{
	static CharacterLvProp prop;
	int lv = getIndexLv(index);
	isOk = false;
	for (auto& prop : lvProps_)
	{
		if (prop.getLv() == lv
			&& isIndexBreak(index) == prop.getIsBreak())
		{
			isOk = true;
			return prop;
		}
	}
	return prop;
}

CharacterLvProp& CharacterLvPropModel::getLvProp(const QModelIndex& index, bool& isOk)
{
	const CharacterLvPropModel* cthis = this;
	return const_cast<CharacterLvProp&>(cthis->getLvProp(index, isOk));
}

