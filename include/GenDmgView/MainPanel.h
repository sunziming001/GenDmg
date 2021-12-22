#ifndef _MAIN_PANEL_H
#define _MAIN_PANEL_H

#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QButtonGroup>


enum class PageType{
	Home,
	Character,
};

class MainPanel:public QFrame
{
	Q_OBJECT
public:
	MainPanel(QWidget *parent =nullptr);
signals:
	void sigPageChanged(PageType type);
private:
	QPushButton* createPanelButton(int awsomeIcon);
	void onButtonToggled(QAbstractButton* btn, bool toggled);
private:
	QVBoxLayout *mainLayout_;
	QButtonGroup* btnGroup_;
	QPushButton* btnHome_;
	QPushButton* btnCharacter_;
};

#endif