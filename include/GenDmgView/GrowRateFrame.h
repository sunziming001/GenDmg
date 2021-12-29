#ifndef _GROW_RATE_FRAME_H
#define _GROW_RATE_FRAME_H

#include <QFrame>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableView>

class GrowRateModel;

class GrowRateFrame :public QFrame
{
	Q_OBJECT
public:
	GrowRateFrame(QWidget* parent);
	~GrowRateFrame();
private:
	QFrame *createGrowRateFrame();
private:
	QVBoxLayout* mainLayout_ = nullptr;
	QPushButton* btnAddGrowRate_ = nullptr;

	QTableView* tvGrowRate_ = nullptr;
	GrowRateModel* growRateModel_ = nullptr;
};

#endif