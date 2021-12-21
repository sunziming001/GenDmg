#ifndef AWESOME_FONT_MANAGER_H
#define AWESOME_FONT_MANAGER_H

#include "QtAwesome.h"
#include <QApplication>
class AwesomeFontManager
{
public:
	static AwesomeFontManager* getInstance();
	void init(QApplication& app);
	void uninit();
	~AwesomeFontManager();
	QtAwesome* getQtAwesome();
private:
	AwesomeFontManager();
private:
	static AwesomeFontManager* instance;
	QtAwesome* qtAwesome_;
};

#endif