#include "TitlePanel.h"
#include "AwesomeFontManager.h"
#include <QApplication>

TitlePanel::TitlePanel(QWidget* parent)
{
	setObjectName("TitlePanel");

	mainLayout_ = new QHBoxLayout;
	this->setLayout(mainLayout_);
	mainLayout_->setContentsMargins(0, 2, 4, 0);

	lbTitle_ = new QLabel(tr("GenDmg"), this);
	btnMin_ = createTitleButton(fa::windowminimize);
	btnMaxOrRecover_ = createTitleButton(fa::windowmaximize);
	btnClose_ = createTitleButton(fa::windowcloseo);

	mainLayout_->addStretch(1);
	mainLayout_->addWidget(lbTitle_);
	mainLayout_->addStretch(1);
	mainLayout_->addWidget(btnMin_);
	mainLayout_->addWidget(btnMaxOrRecover_);
	mainLayout_->addWidget(btnClose_);

	connect(btnMin_, &QPushButton::clicked, this, &TitlePanel::onBtnMinClicked);
	connect(btnMaxOrRecover_, &QPushButton::clicked, this, &TitlePanel::onBtnMaxOrRecoverClicked);
	connect(btnClose_, &QPushButton::clicked, this, &TitlePanel::onBtnCloseClicked);
}

QPushButton* TitlePanel::createTitleButton(int faIcon)
{
	AwesomeFontManager* afm = AwesomeFontManager::getInstance();
	QtAwesome* qa = afm->getQtAwesome();

	QPushButton* ret = new QPushButton(this);
	ret->setObjectName("TitleButton");
	ret->setIcon(qa->icon(faIcon));
	ret->setIconSize(QSize(14, 14));
	return ret;
}

void TitlePanel::onBtnMinClicked()
{
	WId wid = effectiveWinId();
	QWidget *w = find(wid);
	w->showMinimized();
}

void TitlePanel::onBtnCloseClicked()
{
	QApplication::quit();
}

void TitlePanel::onBtnMaxOrRecoverClicked()
{
	WId wid = effectiveWinId();
	QWidget* w = find(wid);

	if (isMax_)
	{
		w->showNormal();
		isMax_ = false;
	}
	else {
		w->showMaximized();
		isMax_ = true;
	}
}
