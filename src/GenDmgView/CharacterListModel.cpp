#include "CharacterListModel.h"

CharacterListModel::CharacterListModel(QObject* parent /*= nullptr*/)
{
	refresh();
}

CharacterListModel::~CharacterListModel()
{

}

int CharacterListModel::rowCount(const QModelIndex&) const
{
	return briefs_.size();
}

QVariant CharacterListModel::data(const QModelIndex& index, int role /*= Qt::DisplayRole*/) const
{
	QVariant value;
	int r = index.row();
	if (r<0 || r>=briefs_.size())
	{
		return value;
	}

	switch (role)
	{
	case Qt::DisplayRole:
	case Qt::EditRole:
		value = QString(QObject::tr(briefs_[r].getName().c_str()));
		break;
	case CharacterBriefModelRole::CharacterId:
		value = briefs_[r].getId();
		break;
	case CharacterBriefModelRole::ImageUrl:
		value = QString::fromStdString(briefs_[r].getImgPath());
		break;
	default:
		break;
	}

	return value;
}

void CharacterListModel::refresh()
{
	briefs_ = GenDmgCore::getInstance()->getAllCharacterBrief();
	briefs_.push_back(CharacterBrief());
	QModelIndex topLeft = createIndex(0, 0);

	QModelIndex bottomRight = createIndex(briefs_.size()+1, 1);
	dataChanged(topLeft, bottomRight);
}

