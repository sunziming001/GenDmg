#include "GenDmgApp.h"
#include "GenDmgCore.h"
#include "ViewLogger.h"
#include <QResource>
#include <QFile>
#include "AwesomeFontManager.h"

#define RCC_FILE_PATH "./res.rcc"

GenDmgApp::GenDmgApp(int argc, char** argv)
	:QApplication(argc, argv)
{
	init();
}

GenDmgApp::~GenDmgApp()
{
	uninit();
}

void GenDmgApp::init()
{
	initLogger();
	initRes();
	initGenDmgCore();
	initAwesomeFont();
}

void GenDmgApp::uninit()
{
	uninitAwesomeFont();
	uninitGenDmgCore();
	uninitRes();
	uninitLogger();
}

void GenDmgApp::initRes()
{
	bool ret = QResource::registerResource(RCC_FILE_PATH);
	if (ret)
	{
		LOG_INFO("GenDmgApp","res register success.");
	}
	else {
		LOG_WARN("GenDmgApp", "res register failed.");
		return;
	}

	QFile file(":/res/qss/CommonStyle.qss");
	file.open(QIODeviceBase::ReadOnly);
	QString qss = QString::fromUtf8(file.readAll());
	this->setStyleSheet(qss);
	

	
}

void GenDmgApp::uninitRes()
{
	bool ret = QResource::unregisterResource(RCC_FILE_PATH);
	if (ret)
	{
		LOG_INFO("GenDmgApp", "res unregister success.");
	}
	else {
		LOG_WARN("GenDmgApp", "res unregister failed.");
	}
}

void GenDmgApp::initGenDmgCore()
{
	GenDmgCore::getInstance()->init();
}

void GenDmgApp::uninitGenDmgCore()
{
	GenDmgCore::getInstance()->uninit();
}

void GenDmgApp::initLogger()
{
	LOG_INIT(0)
}

void GenDmgApp::uninitLogger()
{

}

void GenDmgApp::initAwesomeFont()
{
	AwesomeFontManager* mgr = AwesomeFontManager::getInstance();
	mgr->init(*this);
}

void GenDmgApp::uninitAwesomeFont()
{
	AwesomeFontManager* mgr = AwesomeFontManager::getInstance();
	mgr->uninit();
}
