#ifndef _MAIN_FRAME_H
#define _MAIN_FRAME_H

#include <QFrame>
#include <QMouseEvent>
#include <QHBoxLayout>

class MainPanel;
class TitlePanel;

class MainFrame :public QFrame
{
	Q_OBJECT
public:
	MainFrame(QWidget* parent=nullptr);
protected:
	virtual void paintEvent(QPaintEvent* e);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* e);
	virtual bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) Q_DECL_OVERRIDE;

private:
	bool onHandleNCHitTest(const QByteArray& eventType, void* message, qintptr* result);
	
private:
	QPoint mouseDragPos_;
	QVBoxLayout* mainLayout_;
	QHBoxLayout* bodyLayout_;
	MainPanel* mainPanel_;
	TitlePanel* titlePanel_;
};

#endif