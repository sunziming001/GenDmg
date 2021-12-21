#include "AwesomeFontManager.h"

AwesomeFontManager* AwesomeFontManager::getInstance()
{
	if (nullptr == instance)
		instance = new AwesomeFontManager;

	return instance;
}

void AwesomeFontManager::init(QApplication& app)
{
	qtAwesome_ = new QtAwesome(&app);
	qtAwesome_->initFontAwesome();
}

void AwesomeFontManager::uninit()
{
	
}

AwesomeFontManager::~AwesomeFontManager()
{

}

QtAwesome* AwesomeFontManager::getQtAwesome()
{
	return qtAwesome_;
}

AwesomeFontManager::AwesomeFontManager()
	:qtAwesome_(nullptr)
{

}

AwesomeFontManager* AwesomeFontManager::instance=nullptr;

