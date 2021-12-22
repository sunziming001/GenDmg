#ifndef _CHARACTER_FRAME_H
#define _CHARACTER_FRAME_H

#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <vector>
#include "CharacterBrief.h"
#include <QComboBox>
#include <QAbstractListModel>

class MyModel :public QAbstractListModel
{
public:
	MyModel(QObject* parent = nullptr)
		:QAbstractListModel(parent)
	{

	}
	~MyModel()
	{}

	/*virtual QModelIndex index(int row, int col, const QModelIndex&) const
	{
		static int i = 0;
		return createIndex(row, col,i++);
	}
	virtual QModelIndex parent(const QModelIndex& ) const
	{
		return QModelIndex();
	}

	virtual int columnCount(const QModelIndex&) const
	{
		return 4;
	}*/

	virtual int rowCount(const QModelIndex&) const
	{
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const
	{
		QVariant value;
		switch (role)
		{
		case Qt::DisplayRole:
		{
			value = index.row() + index.column();
		}
		break;
		default:
			break;
		}
		return value;
	}
};

class CharacterFrame:public QFrame
{
	Q_OBJECT
public:
	CharacterFrame(QWidget* parent);
	~CharacterFrame();
private:
	QFrame* createConfigView();
	QComboBox* createCharacterSearcher();
private:
	QVBoxLayout* mainLayout_ =nullptr;


	QWidget* configView_ = nullptr;
	QHBoxLayout *configLayout_ = nullptr;
	QLabel* lbCharacterImg_ = nullptr;

	QComboBox* cbCharacterSeacher_ = nullptr;
	QVBoxLayout* configSearchLayout_ = nullptr;


	std::vector<CharacterBrief> allCharacterBrief_;
};



#endif