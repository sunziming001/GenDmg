#ifndef _MAIN_PANEL_H
#define _MAIN_PANEL_H

#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QButtonGroup>

class MainPanel:public QFrame
{
public:
	MainPanel(QWidget *parent =nullptr);
private:
	QPushButton* createPanelButton(int awsomeIcon);
private:
	QVBoxLayout *mainLayout_;
	QButtonGroup* btnGroup_;
	QPushButton* btnHome_;
	QPushButton* btnCharacter_;
};

#endif