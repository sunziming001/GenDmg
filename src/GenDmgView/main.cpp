#include <QApplication>
#include "MainFrame.h"
#include "GenDmgCore.h"
#include "ViewLogger.h"

int main(int argc, char** argv)
{
	LOG_INIT(0);
	LOG_INFO("Main", "start...");

	GenDmgCore* core = GenDmgCore::getInstance();
	core->init();

	QApplication a(argc, argv);
	MainFrame mainFrame;
	mainFrame.show();
	a.exec();

	core->uninit();

	LOG_INFO("Main", "end");
	return 0;
}