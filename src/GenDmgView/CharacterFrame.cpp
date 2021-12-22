#include "CharacterFrame.h"
#include "AwesomeFontManager.h"
#include "GenDmgCore.h"

CharacterFrame::CharacterFrame(QWidget* parent)
	:QFrame(parent)
{
	allCharacterBrief_ = GenDmgCore::getInstance()->getAllCharacterBrief();

	mainLayout_ = new QVBoxLayout;
	mainLayout_->setContentsMargins(2, 4, 2, 0);
	this->setLayout(mainLayout_);

	configView_ = createConfigView();


	mainLayout_->addWidget(configView_);
	mainLayout_->addStretch(1);
}

CharacterFrame::~CharacterFrame()
{

}

QFrame* CharacterFrame::createConfigView()
{
	AwesomeFontManager* afm = AwesomeFontManager::getInstance();
	QtAwesome* qa = afm->getQtAwesome();

	QFrame* frame = new QFrame(this);
	configLayout_ = new QHBoxLayout;
	configLayout_->setContentsMargins(0, 0, 0, 0);
	
	lbCharacterImg_ = new QLabel(frame);
	lbCharacterImg_->setObjectName("CharacterImgLabel");
	QIcon icon = qa->icon(fa::question);
	lbCharacterImg_->setPixmap(icon.pixmap(208, 248));

	configSearchLayout_ = new QVBoxLayout;
	configSearchLayout_->setContentsMargins(0, 0, 0, 0);
	cbCharacterSeacher_ = createCharacterSearcher();


	configSearchLayout_->addWidget(cbCharacterSeacher_);

	configLayout_->addWidget(lbCharacterImg_);
	configLayout_->addLayout(configSearchLayout_);
	configLayout_->addStretch(1);
	frame->setLayout(configLayout_);
	return frame;
}

QComboBox* CharacterFrame::createCharacterSearcher()
{
	QComboBox* ret = new QComboBox(this);
	ret->setPlaceholderText(tr("input character name here"));
	ret->setEditable(true);
	ret->setModel(new MyModel(this));
	for (auto brief : allCharacterBrief_)
	{
		ret->addItem(tr(brief.getName().c_str()));
	}

	return ret;
}
