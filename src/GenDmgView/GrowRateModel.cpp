#include "GrowRateModel.h"

GrowRateModel::GrowRateModel(QObject* parent /*= nullptr*/)
{
	resetFromDB();
}

GrowRateModel::~GrowRateModel()
{

}

int GrowRateModel::rowCount(const QModelIndex&) const
{
	return growRates_.size()+1;
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

Qt::ItemFlags GrowRateModel::flags(const QModelIndex& index) const
{
	Qt::ItemFlags flags = QAbstractTableModel::flags(index);
	if (index.row() >= 1 && index.column() >= 1)
	{
		flags|= Qt::ItemIsEditable;
	}
	return flags;
}

bool GrowRateModel::setData(const QModelIndex& index, const QVariant& value, int role /*= Qt::EditRole*/)
{
	bool ret = false;
	switch (role)
	{
	case Qt::EditRole:
		ret = setEditData(index, value);
		break;
	case Qt::DisplayRole:
	default:
		ret = QAbstractTableModel::setData(index, value, role);
		break;
	}
	if (ret)
	{
		emit dataChanged(index, index);
	}

	return ret;
}

void GrowRateModel::addEmptyGrowRate()
{
	GrowRateModelLine line;
	growRates_.push_back(line);

	emit layoutChanged();
}

void GrowRateModel::resetFromDB()
{
	growRates_.clear();
	auto rates = GenDmgCore::getInstance()->selectAllGrowRate();
	for (auto rate : rates)
	{
		GrowRateModelLine line;
		line.growRate = rate;
		line.isInDb = true;
		growRates_.push_back(line);
	}

	emit layoutChanged();
	emitDataChanged();
}

void GrowRateModel::saveToDB()
{
	for (auto& line : growRates_)
	{
		if (line.isInDb)
		{
			GenDmgCore::getInstance()->updateGrowRate(line.growRate);
		}
		else {
			GenDmgCore::getInstance()->insertGrowRate(line.growRate);
		}
	}
	resetFromDB();
}

QVariant GrowRateModel::getDispalyData(const QModelIndex& index) const
{
	QVariant ret="--";
	if (index.row() == 0)
	{
		ret = getHeaderData(index.column());
	}
	else{
		int col = index.column();
		int i = index.row() - 1;
		const GrowRateModelLine& line = growRates_.at(i);
		if (col == 0)
		{
			ret = line.growRate.getId();
		}
		else if (col == 1)
		{
			ret = QString::fromUtf8(line.growRate.getName().c_str());
		}
		else {
			int lv = col - 1;
			QString str = QString::number(line.growRate.getLvRate(lv));
			ret = str;
		}
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

bool GrowRateModel::setEditData(const QModelIndex& index, const QVariant& value)
{
	bool ret = false;
	int i = index.row() - 1;
	int col = index.column();
	if(i>=0 && i<growRates_.size())
	{ 
		if (col == 1)
		{
			growRates_[i].growRate.setName(value.toString().toUtf8().data());
			ret = true;
		}
		else if (col > 1)
		{
			int lv = col - 1;
			growRates_[i].growRate.setLvRate(lv, value.toDouble());
			ret = true;
		}
	}

	return ret;
}

void GrowRateModel::emitDataChanged()
{
	QModelIndex topLeft = createIndex(0, 0);
	QModelIndex bottomRight = createIndex(growRates_.size(), ColCnt - 1);
	emit dataChanged(topLeft, bottomRight);
}
