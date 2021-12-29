#ifndef _MAIN_FRAME_H
#define _MAIN_FRAME_H

#include <QFrame>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QStackedLayout>

class MainPanel;
class TitlePanel;
class CharacterFrame;
class GrowRateFrame;

enum class PageType;

class MainFrame :public QFrame
{
	Q_OBJECT
public:
	MainFrame(QWidget* parent=nullptr);
protected:
	virtual void paintEvent(QPaintEvent* e);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* e);
	virtual void mouseReleaseEvent(QMouseEvent* e);
	virtual bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) Q_DECL_OVERRIDE;

private:
	bool onHandleNCHitTest(const QByteArray& eventType, void* message, qintptr* result);
	QWidget* createContainer(QWidget* widget);
	void onPageChanged(PageType type);
private:
	bool isWindowDragging_ = false;
	QPoint mouseDragPos_;
	QVBoxLayout* mainLayout_;
	QHBoxLayout* bodyLayout_;
	MainPanel* mainPanel_;
	TitlePanel* titlePanel_;
	QStackedLayout* stackLayout_ = nullptr;
	CharacterFrame* characterFrame_ = nullptr;
	GrowRateFrame* growRateFrame_ = nullptr;

	int characterFrameIndex_ = 0;
	int homeFrameIndex_ = 0;
	int growFrameIndex_ = 0;
};

#endif