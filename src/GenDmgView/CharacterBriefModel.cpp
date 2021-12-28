#include "CharacterBriefModel.h"


CharacterBriefModel::CharacterBriefModel(int charId, QObject* parent /*= nullptr*/)
	:QAbstractTableModel(parent)
{
	resetCharacterId(charId);
}

CharacterBriefModel::~CharacterBriefModel()
{

}

int CharacterBriefModel::rowCount(const QModelIndex&) const
{
	return RowCnt;
}

int CharacterBriefModel::columnCount(const QModelIndex&) const
{
	return ColCnt;
}

QVariant CharacterBriefModel::data(const QModelIndex& index, int role /*= Qt::DisplayRole*/) const
{
	QVariant ret;
	switch (role)
	{
	case Qt::DisplayRole:
		ret = getDisplayRole(index);
		break;
	case Qt::EditRole:
		ret = getEditRole(index);
		break;
	default:
		break;
	}
	return ret;
}

Qt::ItemFlags CharacterBriefModel::flags(const QModelIndex& index) const
{
	Qt::ItemFlags ret = QAbstractTableModel::flags(index);
	if (isNameIndex(index)
		|| isDamageTypeIndex(index)
		|| isImgPathIndex(index))
	{
		ret |= Qt::ItemIsEditable;
	}

	return ret;
}

bool CharacterBriefModel::setData(const QModelIndex& index, const QVariant& value, int role /*= Qt::EditRole*/)
{
	bool ret = false;
	if (isDamageTypeIndex(index))
	{
		brief_.setDmgType(static_cast<DamageType>(value.toInt()));
		ret = true;
	}
	else if (isNameIndex(index))
	{
		brief_.setName(value.toString().toUtf8().data());
		ret = true;
	}
	else if (isImgPathIndex(index))
	{
		brief_.setImgPath(value.toString().toUtf8().data());
		ret = true;
	}
	else {
		ret = QAbstractTableModel::setData(index, value, role);
	}

	if (ret)
	{
		GenDmgCore::getInstance()->updateCharacterBreif(brief_);
		emit dataChanged(index, index);
	}
	return ret;
}

void CharacterBriefModel::resetCharacterId(int charId)
{
	bool isOk = false;
	brief_ = GenDmgCore::getInstance()->selectCharacterBrief(charId, isOk);
	charId_ = charId;

	QModelIndex topLeft = createIndex(0, 0);
	QModelIndex bottomRight = createIndex(RowCnt - 1, ColCnt - 1);
	dataChanged(topLeft, bottomRight);
	
}

QString CharacterBriefModel::damageTypeToString(DamageType type)
{
	QString ret;
	switch (type)
	{
	case DamageType::Fire:
		ret = tr("Fire");
		break;
	case DamageType::Water:
		ret = tr("Water");
		break;
	case DamageType::Wood:
		ret = tr("Wood");
		break;
	case DamageType::Thunder:
		ret = tr("Thunder");
		break;
	case DamageType::Wind:
		ret = tr("Wind");
		break;
	case DamageType::Ice:
		ret = tr("Ice");
		break;
	case DamageType::Stone:
		ret = tr("Stone");
		break;
	case DamageType::Physic:
	case DamageType::Count:
	case DamageType::None:
	default:
		ret = tr("None");
		break;
	}
	return ret;
}

bool CharacterBriefModel::isNameIndex(const QModelIndex& index)
{
	return index.row() == 1 && index.column() == 2;
}

bool CharacterBriefModel::isDamageTypeIndex(const QModelIndex& index)
{
	return index.row() == 1 && index.column() == 1;
}

bool CharacterBriefModel::isImgPathIndex(const QModelIndex& index)
{
	return index.row() == 1 && index.column() == 3;
}

QVariant CharacterBriefModel::getDisplayRole(const QModelIndex& index)const
{
	QVariant ret;
	if (index.row() == 0)
	{
		switch (index.column())
		{
		case 0:
			ret = tr("id");
			break;
		case 1:
			ret = tr("DmgType");
			break;
		case 2:
			ret = tr("name");
			break;
		case 3:
			ret = tr("ImgPath");
			break;
		default:
			break;
		}
	}
	else if (index.row() == 1) {
		switch (index.column())
		{
		case 0:
			ret = brief_.getId();
			break;
		case 1:
			ret = damageTypeToString(brief_.getDmgType());
			break;
		case 2:
			ret = QObject::tr(brief_.getName().c_str());
			break;
		case 3:
			ret = brief_.getImgPath().c_str();
			break;
		default:
			break;
		}

	}

	return ret;
}

QVariant CharacterBriefModel::getEditRole(const QModelIndex& index)const
{
	QVariant ret;
	if (index.row() == 1) {

		switch (index.column())
		{
		case 0:
			ret = brief_.getId();
			break;
		case 1:
			ret = static_cast<int>(brief_.getDmgType());
			break;
		case 2:
			ret = QString::fromStdString(brief_.getName());
			break;
		case 3:
			ret = QString::fromStdString(brief_.getImgPath());
			break;
		default:
			break;
		}

	}
	return ret;
}


