#include "WidgetUtil.h"
#include "AwesomeFontManager.h"


QPushButton* WidgetUtil::createOperBtn(QWidget* parent)
{
	QPushButton* btn = new QPushButton(parent);
	btn->setObjectName("CharacterOperButton");
	btn->setIconSize(QSize(23, 23));
	return btn;
}

QPushButton* WidgetUtil::createSaveBtn(QWidget* parent)
{
	AwesomeFontManager* afm = AwesomeFontManager::getInstance();
	QtAwesome* qa = afm->getQtAwesome();
	QPushButton* btn = createOperBtn(parent);
	btn->setIcon(qa->icon(fa::save));

	return btn;
}

QPushButton* WidgetUtil::createRevertBtn(QWidget* parent)
{
	AwesomeFontManager* afm = AwesomeFontManager::getInstance();
	QtAwesome* qa = afm->getQtAwesome();
	QPushButton* btn = createOperBtn(parent);
	btn->setIcon(qa->icon(fa::reply));

	return btn;
}

QPushButton* WidgetUtil::createAddBtn(QWidget* parent)
{
	AwesomeFontManager* afm = AwesomeFontManager::getInstance();
	QtAwesome* qa = afm->getQtAwesome();
	QPushButton* btn = createOperBtn(parent);
	btn->setIcon(qa->icon(fa::plus));

	return btn;
}
