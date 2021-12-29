#include "MainPanel.h"
#include "AwesomeFontManager.h"
#include <QApplication>
#include <QString>
MainPanel::MainPanel(QWidget* parent /*=nullptr*/)
	:QFrame(parent)
{
	setObjectName("MainPanel");

	btnGroup_ = new QButtonGroup(this);
	btnGroup_->setExclusive(true);

	mainLayout_ = new QVBoxLayout(this);
	mainLayout_->setContentsMargins(8, 8, 0, 0);
	this->setLayout(mainLayout_);


	btnHome_ = createPanelButton(fa::home);
	btnCharacter_ = createPanelButton(fa::child);
	btnGrowRate_ = createPanelButton(fa::table);

	mainLayout_->addWidget(btnHome_);
	mainLayout_->addWidget(btnCharacter_);
	mainLayout_->addWidget(btnGrowRate_);

	mainLayout_->addStretch(1);

	connect(btnGroup_, &QButtonGroup::buttonToggled, this, &MainPanel::onButtonToggled);
}

QPushButton* MainPanel::createPanelButton(int awsomeIcon)
{
	AwesomeFontManager* afm = AwesomeFontManager::getInstance();
	QtAwesome* qa = afm->getQtAwesome();

	QPushButton* ret = new QPushButton(this);
	ret->setObjectName("MainPanelButton");
	ret->setCheckable(true);
	ret->setChecked(false);
	ret->setIconSize(QSize(30, 30));
	ret->setIcon(qa->icon(awsomeIcon));

	btnGroup_->addButton(ret);

	return ret;
}

void MainPanel::onButtonToggled(QAbstractButton* btn, bool toggled)
{
	if (toggled)
	{
		if (btn == btnHome_)
		{
			emit sigPageChanged(PageType::Home);
		}else if(btn==btnCharacter_){
			emit sigPageChanged(PageType::Character);
		}
		else if (btn == btnGrowRate_)
		{
			emit sigPageChanged(PageType::GrowRate);
		}
	}
}
