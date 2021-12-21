#include "MainPanel.h"
#include "AwesomeFontManager.h"
#include <QApplication>
#include <QString>
MainPanel::MainPanel(QWidget* parent /*=nullptr*/)
	:QFrame(parent)
	, mainLayout_(nullptr)
	, btnCharacter_(nullptr)
	, btnGroup_(nullptr)
{
	setObjectName("MainPanel");

	btnGroup_ = new QButtonGroup(this);
	btnGroup_->setExclusive(true);

	mainLayout_ = new QVBoxLayout(this);
	mainLayout_->setContentsMargins(8, 8, 0, 0);
	this->setLayout(mainLayout_);


	btnHome_ = createPanelButton(fa::home);
	btnCharacter_ = createPanelButton(fa::child);

	mainLayout_->addWidget(btnHome_);
	mainLayout_->addWidget(btnCharacter_);
	mainLayout_->addStretch(1);
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
