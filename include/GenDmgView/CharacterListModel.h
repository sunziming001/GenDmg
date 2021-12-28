#ifndef _CHARACTER_LIST_MODEL_H
#define _CHARACTER_LIST_MODEL_H

#include <QAbstractListModel>
#include "GenDmgCore.h"

enum class CharacterBriefModelRole
{
	CharacterId = 0x101,
	ImageUrl,
};

class CharacterListModel :public QAbstractListModel
{
	Q_OBJECT
public:
	CharacterListModel( QObject* parent = nullptr);
	~CharacterListModel();

	int rowCount(const QModelIndex&) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	void refresh();
private:
	std::vector<CharacterBrief> briefs_;

};


#endif