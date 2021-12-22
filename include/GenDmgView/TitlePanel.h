#ifndef _TITLE_PANEL_H
#define _TITLE_PANEL_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

class TitlePanel :public QFrame
{
	Q_OBJECT
public:
	TitlePanel(QWidget* parent);

private:
	QPushButton* createTitleButton(int faIcon);
	void onBtnMinClicked();
	void onBtnCloseClicked();
	void onBtnMaxOrRecoverClicked();
private:
	QHBoxLayout* mainLayout_ = nullptr;
	QLabel* lbTitle_ = nullptr;
	QPushButton* btnMin_ = nullptr;
	QPushButton* btnMaxOrRecover_ = nullptr;
	QPushButton* btnClose_ = nullptr;
	bool isMax_ = false;
};


#endif