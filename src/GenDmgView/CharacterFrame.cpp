#include "CharacterFrame.h"
#include "AwesomeFontManager.h"
#include "CharacterListModel.h"
#include "GenDmgCore.h"
#include <QLineEdit>
#include "CharacterLvPropModel.h"
#include <QTableView>
#include <QHeaderView>
#include "CharacterLvPropDelegate.h"
#include "CharacterBriefModel.h"
#include "CharacterBriefDelegate.h"
#include "WidgetUtil.h"

CharacterFrame::CharacterFrame(QWidget* parent)
	:QFrame(parent)
{
	allCharacterBrief_ = GenDmgCore::getInstance()->getAllCharacterBrief();

	mainLayout_ = new QVBoxLayout;
	mainLayout_->setContentsMargins(2, 4, 2, 0);
	this->setLayout(mainLayout_);

	QFrame *briefFrame = createBriefTable();
	QFrame *lvPropFrame = createLvPropTable();
	
	configView_ = createConfigView();



	mainLayout_->addWidget(configView_);
	mainLayout_->addWidget(briefFrame);
	mainLayout_->addSpacing(5);
	mainLayout_->addWidget(lvPropFrame);
	mainLayout_->addStretch(1);

	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
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
	configSearchLayout_->addStretch(1);

	configLayout_->addWidget(lbCharacterImg_);
	configLayout_->addLayout(configSearchLayout_);
	configLayout_->addStretch(1);


	frame->setLayout(configLayout_);
	return frame;
}

QComboBox* CharacterFrame::createCharacterSearcher()
{
	cbCharacterSeacher_ = new QComboBox(this);
	cbCharacterListModel_ = new CharacterListModel(cbCharacterSeacher_);

	cbCharacterSeacher_->setObjectName("CharacterSearcherComboBox");
	cbCharacterSeacher_->setEditable(true);
	cbCharacterSeacher_->lineEdit()->setPlaceholderText(tr("input character name here"));
	cbCharacterSeacher_->setModel(cbCharacterListModel_);
	
	connect(cbCharacterSeacher_, &QComboBox::currentIndexChanged, this, &CharacterFrame::onCharacterSearcherIndexChaged);
	cbCharacterSeacher_->setCurrentIndex(cbCharacterSeacher_->count());
	return cbCharacterSeacher_;
}

QFrame* CharacterFrame::createLvPropTable()
{
	QFrame* frame = new QFrame(this);
	tvLvProps_ = new QTableView(frame);
	tvLvPropsModel_ = new CharacterLvPropModel(-1, this);

	QVBoxLayout* frameLayout = new QVBoxLayout;
	frameLayout->setContentsMargins(0, 0, 0, 0);

	QHBoxLayout* btnLayout = new QHBoxLayout;
	btnLayout->setContentsMargins(0, 0, 0, 0);

	QPushButton* btnSave = WidgetUtil::createSaveBtn(frame);
	QPushButton* btnRevert = WidgetUtil::createRevertBtn(frame);

	tvLvProps_->setObjectName("LvPropsTableView");

	tvLvProps_->setModel(tvLvPropsModel_);
	tvLvProps_->setItemDelegate(new CharacterLvPropDelegate(tvLvProps_));

	tvLvProps_->horizontalHeader()->setVisible(false);
	tvLvProps_->verticalHeader()->setVisible(false);
	tvLvProps_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tvLvProps_->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	tvLvProps_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	tvLvProps_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	tvLvProps_->setSpan(0, 1, 1, 2);
	tvLvProps_->setSpan(0, 3, 1, 2);
	tvLvProps_->setSpan(0, 5, 1, 2);
	tvLvProps_->setSpan(0, 7, 1, 2);
	tvLvProps_->setSpan(0, 0, 2, 1);
	tvLvProps_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
	

	btnLayout->addWidget(btnSave);
	btnLayout->addWidget(btnRevert);
	btnLayout->addStretch(1);

	frameLayout->addLayout(btnLayout);
	frameLayout->addWidget(tvLvProps_);
	frameLayout->addStretch(1);

	frame->setLayout(frameLayout);
	
	connect(btnSave, &QPushButton::clicked, this, [this]() {
		tvLvPropsModel_->saveToDB();

	});

	connect(btnRevert, &QPushButton::clicked, this, [this]() {
		tvLvPropsModel_->resetFromDB();
	});

	return frame;
}

QFrame* CharacterFrame::createBriefTable()
{
	QFrame* frame = new QFrame(this);
	QVBoxLayout* frameLayout = new QVBoxLayout;
	frameLayout->setContentsMargins(0, 0, 0, 0);

	QHBoxLayout* btnLayout = new QHBoxLayout;
	btnLayout->setContentsMargins(0, 0, 0, 0);

	QPushButton* btnSave = WidgetUtil::createSaveBtn(frame);
	QPushButton* btnRevert = WidgetUtil::createRevertBtn(frame);

	tvBrief_ = new QTableView(frame);

	tvBriefModel_ = new CharacterBriefModel(-1,tvBrief_);

	tvBrief_->setObjectName("CharacterBriefTableView");
	tvBrief_->setModel(tvBriefModel_);
	tvBrief_->setItemDelegate(new CharacterBriefDelegate(tvBrief_));

	tvBrief_->setWordWrap(false);
	tvBrief_->horizontalHeader()->setVisible(false);
	tvBrief_->verticalHeader()->setVisible(false);
	tvBrief_->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	tvBrief_->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tvBrief_->horizontalHeader()->setStretchLastSection(true);
	tvBrief_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	tvBrief_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	btnLayout->addWidget(btnSave);
	btnLayout->addWidget(btnRevert);
	btnLayout->addStretch(1);

	frameLayout->addLayout(btnLayout);
	frameLayout->addWidget(tvBrief_);
	frameLayout->addStretch(1);

	frame->setLayout(frameLayout);

	connect(btnSave, &QPushButton::clicked, this, [this]() {
		tvBriefModel_->saveToDB();

		if (cbCharacterListModel_)
		{
			cbCharacterListModel_->refresh();
			refreshCharacterImage();
		}
	});

	connect(btnRevert, &QPushButton::clicked, this, [this]() {
		tvBriefModel_->resetFromDB();
	});


	return frame;
}

void CharacterFrame::onCharacterSearcherIndexChaged(int indx)
{
	int charId = cbCharacterSeacher_->itemData(indx, static_cast<int>(CharacterBriefModelRole::CharacterId)).toInt();
	
	refreshCharacterImage();

	if (tvLvPropsModel_)
	{
		tvLvPropsModel_->resetCharacterId(charId);
	}

	if (tvBriefModel_)
	{
		tvBriefModel_->resetCharacterId(charId);
	}
	
}

void CharacterFrame::refreshCharacterImage()
{
	int indx = cbCharacterSeacher_->currentIndex();
	AwesomeFontManager* afm = AwesomeFontManager::getInstance();
	QtAwesome* qa = afm->getQtAwesome();

	QString path = cbCharacterSeacher_->itemData(indx, static_cast<int>(CharacterBriefModelRole::ImageUrl)).toString();
	

	QPixmap img(path);
	if (img.isNull())
	{
		QIcon icon = qa->icon(fa::question);
		lbCharacterImg_->setPixmap(icon.pixmap(208, 248));
	}
	else {
		img = img.scaled(lbCharacterImg_->size());
		lbCharacterImg_->setPixmap(img);
	}
}
