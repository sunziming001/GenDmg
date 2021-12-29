#include "GrowRateModel.h"

GrowRateModel::GrowRateModel(QObject* parent /*= nullptr*/)
{

}

GrowRateModel::~GrowRateModel()
{

}

int GrowRateModel::rowCount(const QModelIndex&) const
{
	return 2;
}

int GrowRateModel::columnCount(const QModelIndex&) const
{
	return ColCnt;
}

QVariant GrowRateModel::data(const QModelIndex& index, int role /*= Qt::DisplayRole*/) const
{
	QVariant ret;
	switch (role)
	{
	case Qt::DisplayRole:
		ret = getDispalyData(index);
		break;
	default:
		break;
	}
	return ret;
}

QVariant GrowRateModel::getDispalyData(const QModelIndex& index) const
{
	QVariant ret;
	if (index.row() == 0)
	{
		ret = getHeaderData(index.column());
	}

	return ret;
}

QVariant GrowRateModel::getHeaderData(int col) const
{
	QVariant ret;
	if (col == 0)
	{
		ret = tr("id");
	}
	else if (col == 1)
	{
		ret = tr("name");
	}
	else {
		ret = tr("lv%1").arg(col-1);
	}

	return ret;
}
