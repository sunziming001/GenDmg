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
	case Qt::DisplayRole:
		value = getDisplayString(index);
		break;
	}

	return value;
}

QString CharacterLvPropModel::getDisplayString(const QModelIndex& index) const
{
	QString ret = "--";
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
	else if (index.row() == 0 && index.column() == 7)
	{
		ret = getSpecialPropName();
	}
	else if (index.row() == 1 && index.column() != 0)
	{
		if (index.column() % 2 == 0)
		{
			ret = tr("bef break");
		}
		else {
			ret = tr("aft break");
		}
	}
	else if (index.column() == 0)
	{
		switch (index.row())
		{
		case 2:
			ret = "1";
			break;
		case 3:
			ret = "20";
			break;
		case 4:
			ret = "40";
			break;
		case 5:
			ret = "50";
			break;
		case 6:
			ret = "60";
			break;
		case 7:
			ret = "70";
			break;
		case 8:
			ret = "80";
			break;
		case 9:
			ret = "90";
			break;
		}
	}

	return ret;
}

QString CharacterLvPropModel::getSpecialPropName() const
{
	QString ret = "--";
	if (lvProps_.size() > 0)
	{
		SpecialPropType type = lvProps_[0].getSpPropType();
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
	}

	return ret;
}

