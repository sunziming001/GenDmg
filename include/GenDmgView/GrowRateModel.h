#ifndef _GROW_RATE_MODEL_H
#define _GROW_RATE_MODEL_H

#include <QAbstractTableModel>
#include "GenDmgCore.h"

typedef struct _GrowRateModelLine
{
	CharacterGrowRate growRate;
	bool isInDb = false;
}GrowRateModelLine;


class GrowRateModel :public QAbstractTableModel
{
	Q_OBJECT
public:
	static const int ColCnt = 15;
	GrowRateModel(QObject* parent = nullptr);
	~GrowRateModel();

	int rowCount(const QModelIndex&) const override;
	int columnCount(const QModelIndex&) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole)override;

	void addEmptyGrowRate();

	void resetFromDB();
	void saveToDB();
private:
	QVariant getDispalyData(const QModelIndex& index)const;
	QVariant getHeaderData(int col)const;

	bool setEditData(const QModelIndex& index, const QVariant& value);
	void emitDataChanged();
private:
	std::vector<GrowRateModelLine> growRates_;
};

#endif