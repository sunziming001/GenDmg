#ifndef _CHARACTER_BRIEF_MODEL_H
#define _CHARACTER_BRIEF_MODEL_H

#include <QAbstractListModel>
#include "GenDmgCore.h"

enum class CharacterBriefModelRole
{
	CharacterId = 0x101,
	ImageUrl,
};

class CharacterBriefModel :public QAbstractListModel
{
	Q_OBJECT
public:
	CharacterBriefModel( QObject* parent = nullptr);
	~CharacterBriefModel();

	int rowCount(const QModelIndex&) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
private:
	std::vector<CharacterBrief> briefs_;

};


#endif