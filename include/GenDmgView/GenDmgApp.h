#ifndef _GEN_DMG_APP_H
#define _GEN_DMG_APP_H

#include <QApplication>

class GenDmgApp :public QApplication
{
public:
	GenDmgApp(int argc, char** argv);
	~GenDmgApp();
private:
	void init();
	void uninit();

	void initRes();
	void uninitRes();

	void initGenDmgCore();
	void uninitGenDmgCore();

	void initLogger();
	void uninitLogger();
};

#endif