#include "MainFrame.h"
#include <QPainter>
#include <QStyleOption>
#include <windows.h>
#include <QApplication>
#include <QPushButton>
#include "AwesomeFontManager.h"
#include "MainPanel.h"
#include "TitlePanel.h"
#include "CharacterFrame.h"
#include <QScrollArea>


MainFrame::MainFrame(QWidget* parent)
	:QFrame(parent)
	, mainLayout_(nullptr)
	, mainPanel_(nullptr)
	, titlePanel_(nullptr)
{
	this->setObjectName("MainFrame");
	this->setWindowFlag(Qt::Window);
	this->setWindowFlag(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground);
	this->setAttribute(Qt::WA_NativeWindow);

	mainLayout_ = new QVBoxLayout;
	mainLayout_->setContentsMargins(0, 0, 0, 0);
	this->setLayout(mainLayout_);

	bodyLayout_ = new QHBoxLayout;
	bodyLayout_->setContentsMargins(0, 0, 0, 0);

	titlePanel_ = new TitlePanel(this);
	mainPanel_ = new MainPanel(this);
	characterFrame_ = new CharacterFrame(this);

	stackedLayout_ = new QStackedLayout(this);
	stackedLayout_->setStackingMode(QStackedLayout::StackOne);
	
	homeFrameIndex_ = stackedLayout_->addWidget(createContainer(new QFrame(this)));
	characterFrameIndex_ = stackedLayout_->addWidget(createContainer(characterFrame_));

	mainLayout_->addWidget(titlePanel_);
	mainLayout_->addLayout(bodyLayout_, 1);

	bodyLayout_->addWidget(mainPanel_);
	bodyLayout_->addLayout(stackedLayout_, 1);


	connect(mainPanel_, &MainPanel::sigPageChanged, this, &MainFrame::onPageChanged);
}

void MainFrame::paintEvent(QPaintEvent* e)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);

	// Have style sheet?
	if (testAttribute(Qt::WA_StyleSheetTarget)) {
		// Let QStylesheetStyle have its way with us.
		QStyleOption opt;
		opt.initFrom(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		p.end();
		return;
	}

}

void MainFrame::mousePressEvent(QMouseEvent* e)
{
	mouseDragPos_ = e->globalPos();
}

void MainFrame::mouseMoveEvent(QMouseEvent* e)
{
	const QPoint delta = e->globalPos() - mouseDragPos_;
	move(x() + delta.x(), y() + delta.y());
	mouseDragPos_ = e->globalPos();
}

bool MainFrame::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
{
	MSG* msg = static_cast<MSG*>(message);

	switch (msg->message)
	{
	case WM_NCCALCSIZE:
		if (msg->wParam)
		{
			// do not change rect[0], keep no nc-borders

			// should return 0
			*result = 0;

			DWORD dwOldStyle = GetWindowLong(msg->hwnd, GWL_STYLE);
			if (0 == (dwOldStyle & WS_THICKFRAME))
			{
				SetWindowLong(msg->hwnd, GWL_STYLE, dwOldStyle
					| WS_THICKFRAME   // HTLEFT, HTRIGHT, ... 会允许改变大小
					| WS_MAXIMIZEBOX // 双击 HTCAPTION 部分，会自动最大化
					| WS_MINIMIZEBOX //
				);
			}
			return true;
		}
		break;
	case WM_NCHITTEST:
		if (onHandleNCHitTest(eventType, message, result))
		{
			return true;
		}
		break;
	default:
		break;
	}


	return false;
}

bool MainFrame::onHandleNCHitTest(const QByteArray& eventType, void* message, qintptr* result)
{
	MSG* msg = static_cast<MSG*>(message);
	if (isMaximized())
	{
		return false;
	}

	*result = 0;
	const LONG borderWidth = 8;
	RECT winrect;
	GetWindowRect(reinterpret_cast<HWND>(winId()), &winrect);

	// must be short to correctly work with multiple monitors (negative coordinates)
	short x = msg->lParam & 0x0000FFFF;
	short y = (msg->lParam & 0xFFFF0000) >> 16;

	bool resizeWidth = minimumWidth() != maximumWidth();
	bool resizeHeight = minimumHeight() != maximumHeight();
	if (resizeWidth)
	{
		//left border
		if (x >= winrect.left && x < winrect.left + borderWidth)
		{
			*result = HTLEFT;
		}
		//right border
		if (x < winrect.right && x >= winrect.right - borderWidth)
		{
			*result = HTRIGHT;
		}
	}
	if (resizeHeight)
	{
		//bottom border
		if (y < winrect.bottom && y >= winrect.bottom - borderWidth)
		{
			*result = HTBOTTOM;
		}
		//top border
		if (y >= winrect.top && y < winrect.top + borderWidth)
		{
			*result = HTTOP;
		}
	}
	if (resizeWidth && resizeHeight)
	{
		//bottom left corner
		if (x >= winrect.left && x < winrect.left + borderWidth &&
			y < winrect.bottom && y >= winrect.bottom - borderWidth)
		{
			*result = HTBOTTOMLEFT;
		}
		//bottom right corner
		if (x < winrect.right && x >= winrect.right - borderWidth &&
			y < winrect.bottom && y >= winrect.bottom - borderWidth)
		{
			*result = HTBOTTOMRIGHT;
		}
		//top left corner
		if (x >= winrect.left && x < winrect.left + borderWidth &&
			y >= winrect.top && y < winrect.top + borderWidth)
		{
			*result = HTTOPLEFT;
		}
		//top right corner
		if (x < winrect.right && x >= winrect.right - borderWidth &&
			y >= winrect.top && y < winrect.top + borderWidth)
		{
			*result = HTTOPRIGHT;
		}
	}

	if (*result != 0)
		return true;

	QWidget* action = QApplication::widgetAt(QCursor::pos());
	if (action == this) {
		*result = HTCAPTION;
		return true;
	}
	return false;
}

QWidget* MainFrame::createContainer(QWidget* widget)
{
	QScrollArea* ret = new QScrollArea(this);
	ret->setObjectName("FrameContainer");
	ret->setWidget(widget);
	ret->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
	ret->setWidgetResizable(true);
	return ret;
}

void MainFrame::onPageChanged(PageType type)
{
	switch (type)
	{
	case PageType::Home:
		stackedLayout_->setCurrentIndex(homeFrameIndex_);
		break;
	case PageType::Character:
		stackedLayout_->setCurrentIndex(characterFrameIndex_);
		break;
	default:
		break;
	}
}
