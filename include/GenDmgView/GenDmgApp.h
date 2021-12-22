#ifndef _GEN_DMG_APP_H
#define _GEN_DMG_APP_H

#include <QApplication>
#include <QTranslator>

class GenDmgApp :public QApplication
{
	Q_OBJECT
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

	void initAwesomeFont();
	void uninitAwesomeFont();
private:
	QTranslator *translator_=new QTranslator(this);
};

#endif