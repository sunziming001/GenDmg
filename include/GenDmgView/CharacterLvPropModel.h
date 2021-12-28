#ifndef CHARACTER_LV_PROP_MODEL_H
#define CHARACTER_LV_PROP_MODEL_H

#include <QAbstractTableModel>
#include "GenDmgCore.h"

class CharacterLvPropModel:public QAbstractTableModel
{
	Q_OBJECT
public:
	static const int RowCnt = 10;
	static const int ColCnt = 9;
	CharacterLvPropModel(int charId, QObject* parent = nullptr);
	~CharacterLvPropModel();

	int rowCount(const QModelIndex&) const override;
	int columnCount(const QModelIndex&) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole)override;
	void resetCharacterId(int charId);

	void saveToDB();

	void resetFromDB();

	static QString specialPropTypeToString(SpecialPropType type);
	static bool isSpecialPropIndex(const QModelIndex& index);
	static bool isIntIndex(const QModelIndex& index);
	static bool isDoubleIndex(const QModelIndex& index);

	static bool isDefIndex(const QModelIndex& index);
	static bool isAtkIndex(const QModelIndex& index);
	static bool isHpIndex(const QModelIndex& index);
	static bool isSpecialPropValIndex(const QModelIndex& index);
	static int getIndexLv(const QModelIndex& index);
	static bool isIndexBreak(const QModelIndex& index);
private:
	QVariant getDisplayData(const QModelIndex& index)const;
	QVariant getEditData(const QModelIndex& index)const;

	bool setEditData(const QModelIndex& index, const QVariant& value);

	QString getSpecialPropName()const;

	QString getLvPropString(const QModelIndex& index)const;
	QVariant getLvPropEditData(const QModelIndex& index)const;
	void setLvPropVarient(const QModelIndex& index, const QVariant& value);
	const CharacterLvProp& getLvProp(const QModelIndex& index, bool& isOk)const;
	CharacterLvProp& getLvProp(const QModelIndex& index, bool& isOk);
private:
	std::vector<CharacterLvProp> lvProps_;
	int charId_;
};

#endif