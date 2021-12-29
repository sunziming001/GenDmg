#ifndef _GROW_RATE_MODEL_H
#define _GROW_RATE_MODEL_H

#include <QAbstractTableModel>

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
private:
	QVariant getDispalyData(const QModelIndex& index)const;
	QVariant getHeaderData(int col)const;
};

#endif