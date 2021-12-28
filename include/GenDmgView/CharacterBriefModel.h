#ifndef CHARACTER_BRIEF_MODEL_H
#define CHARACTER_BRIEF_MODEL_H

#include <QAbstractTableModel>
#include "GenDmgCore.h"

class CharacterBriefModel :public QAbstractTableModel
{
	Q_OBJECT
public:
	static const int RowCnt = 2;
	static const int ColCnt = 4;
	CharacterBriefModel(int charId, QObject* parent = nullptr);
	~CharacterBriefModel();

	int rowCount(const QModelIndex&) const override;
	int columnCount(const QModelIndex&) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole)override;

	void resetCharacterId(int charId);

	static QString damageTypeToString(DamageType type);
	static bool isNameIndex(const QModelIndex& index);
	static bool isDamageTypeIndex(const QModelIndex& index);
	static bool isImgPathIndex(const QModelIndex& index);
private:
	QVariant getDisplayRole(const QModelIndex& index)const;
	QVariant getEditRole(const QModelIndex& index)const;

private:
	int charId_=-1;
	CharacterBrief brief_;
};

#endif