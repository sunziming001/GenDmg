#include "GrowRateFrame.h"
#include "WidgetUtil.h"
#include <QHeaderView>
#include "GrowRateModel.h"

GrowRateFrame::GrowRateFrame(QWidget* parent)
	:QFrame(parent)
{
	mainLayout_ = new QVBoxLayout;
	mainLayout_->setContentsMargins(0, 0, 0, 0);

	QFrame* growRateFrame = createGrowRateFrame();

	mainLayout_->addWidget(growRateFrame);
	mainLayout_->addStretch(1);

	this->setLayout(mainLayout_);
}

GrowRateFrame::~GrowRateFrame()
{

}

QFrame* GrowRateFrame::createGrowRateFrame()
{
	QFrame* frame = new QFrame(this);
	QVBoxLayout* frameLayout = new QVBoxLayout;
	QHBoxLayout* btnLayout = new QHBoxLayout;
	
	btnAddGrowRate_ = WidgetUtil::createAddBtn(this);
	btnSaveAll_ = WidgetUtil::createSaveBtn(this);
	btnRevert_ = WidgetUtil::createRevertBtn(this);

	tvGrowRate_ = new QTableView(frame);
	growRateModel_ = new GrowRateModel(tvGrowRate_);

	tvGrowRate_->setModel(growRateModel_);

	tvGrowRate_->setObjectName("GrowRateTableView");
	tvGrowRate_->horizontalHeader()->setVisible(false);
	tvGrowRate_->verticalHeader()->setVisible(false);

	tvGrowRate_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tvGrowRate_->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	tvGrowRate_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	tvGrowRate_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	tvGrowRate_->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

	btnLayout->addWidget(btnAddGrowRate_);
	btnLayout->addWidget(btnSaveAll_);
	btnLayout->addWidget(btnRevert_);
	btnLayout->addStretch(1);

	frameLayout->addLayout(btnLayout);
	frameLayout->addWidget(tvGrowRate_);

	frame->setLayout(frameLayout);


	connect(btnAddGrowRate_, &QPushButton::clicked, this, [this]() {
		growRateModel_->addEmptyGrowRate();
	});

	connect(btnSaveAll_, &QPushButton::clicked, this, [this]() {
		growRateModel_->saveToDB();
	});

	connect(btnRevert_, &QPushButton::clicked, this, [this]() {
		growRateModel_->resetFromDB();
	});

	return frame;
}
