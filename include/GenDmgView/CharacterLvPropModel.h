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
private:
	QString getDisplayString(const QModelIndex& index)const;
	QString getSpecialPropName()const;
private:
	std::vector<CharacterLvProp> lvProps_;
	int charId_;
};

#endif