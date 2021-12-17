#include "MainFrame.h"

MainFrame::MainFrame(QWidget* parent)
	:QFrame(parent)
{
	this->setWindowFlag(Qt::FramelessWindowHint);
}
