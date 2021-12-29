#ifndef _WIDGET_UTIL_H
#define _WIDGET_UTIL_H

#include <QPushButton>

namespace WidgetUtil
{
	QPushButton* createOperBtn(QWidget* parent);
	QPushButton* createSaveBtn(QWidget* parent);
	QPushButton* createRevertBtn(QWidget* parent);
	QPushButton* createAddBtn(QWidget* parent);
}


#endif;