//
// Created by zhenghu on 16-7-25.
//
#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>
#include <deque>
#include <map>
#include "verdigris/src/wobjectimpl.h"
#include "verdigris/src/wobjectdefs.h"
#include <QtWidgets/QMessageBox>
#include <cstdlib>
#define _DEBUG

#ifdef _DEBUG
#define ACL_ASSERT(_Expression,errStr) (void)( (!!(_Expression)) || (acl_error(errStr),0) )
#else
#define ACL_ASSERT(flag, errStr) ((void)0)
#endif
#define ACL_ASSERT_HWND ACL_ASSERT(pApp!=0, \
    "You should call function \"initWindow(...)\" befor use function \"" __FUNCTION__ "\"" )


extern "C" {
#include "../common/acllib.h"
}

QApplication *pApp = nullptr;
QMainWindow *pMainWindow = nullptr;

void acl_error(char *errStr) {

  msgBox("Fatal Error!", errStr, NULL);
  exit(0);
}

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
};

///
struct Line {
  int startX, startY;
  int endX, endY;
  Line(int startX, int startY, int endX, int endY) : startX(startX), startY(startY), endX(endX), endY(endY) {}
};


class IntTimer: public QTimer {
  W_OBJECT(IntTimer)
 private:
  int id;
 public:
  IntTimer(QObject *parent, int id);
  void fireTimer();
  W_SLOT(fireTimer)
  int timeoutWithId(int id) W_SIGNAL(timeoutWithId, id)
};

W_OBJECT_IMPL(IntTimer)
void IntTimer::fireTimer() {
  emit timeoutWithId(id);
}

IntTimer::IntTimer(QObject *parent, int id) : QTimer(parent), id(id) {
  connect(this, SIGNAL(timeout()), this, SLOT(fireTimer()));
}

int end = 200;
class AclGlobalWidget: public QWidget {
  W_OBJECT(AclGlobalWidget)
 private:
  std::string title;
  Point *currentPoint;
  QTimer *timer;
  std::deque<Line> lines;
  std::map<int, IntTimer *> timers;
  TimerEventCallback timerEventCallback;
 protected:
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void timerListener(int timerId);
  W_SLOT(timerListener)
 public:
  AclGlobalWidget();
  ~AclGlobalWidget();
  ///
  void addLine(int startX, int startY, int endX, int endY);
  void addLineTo(int endX, int endY);
  void update2();
  W_SLOT(update2)
  ///
  void beginPaint();
  void endPaint();
  void clearDevice(void);
  int getWidth();
  int getHeight();
  void registerTimerEvent(TimerEventCallback callback);
  void startTimer(int timerID, int timeinterval);
  void cancelTimer(int timerID);
};
W_OBJECT_IMPL(AclGlobalWidget)

/// Handle mouse press events.
/// \param event
void AclGlobalWidget::mousePressEvent(QMouseEvent *event) {
  qDebug() << event->x();
  if (event->button() == Qt::LeftButton) {
    // handle left mouse button here
  } else {
    // pass on other buttons to base class
  }
}
AclGlobalWidget::AclGlobalWidget() {
  qDebug() << "Creating timer!";
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update2()));
  timer->start(1000);
}
AclGlobalWidget::~AclGlobalWidget() {
  delete timer;
}
void AclGlobalWidget::addLine(int startX, int startY, int endX, int endY) {
  Line newLine(startX, startY, endX, endY);
  lines.push_back(newLine);
}

void AclGlobalWidget::addLineTo(int endX, int endY) {
  Line newLine(currentPoint->x, currentPoint->y, endX, endY);
  lines.push_back(newLine);
}

void AclGlobalWidget::update2() {
  qDebug() << end;
}

void AclGlobalWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
  for (auto &line: lines) {
    painter.drawLine(line.startX, line.startY, line.endX, line.endY);
  }
}

void AclGlobalWidget::timerListener(int timerId) {
  if (timerEventCallback != nullptr) {
    timerEventCallback(timerId);
  }
}

void AclGlobalWidget::beginPaint() {

}
void AclGlobalWidget::endPaint() {
  update();
}
void AclGlobalWidget::clearDevice(void) {

}
int AclGlobalWidget::getWidth() {

}
int AclGlobalWidget::getHeight() {

}

void AclGlobalWidget::registerTimerEvent(TimerEventCallback callback) {
  timerEventCallback = callback;
}


void AclGlobalWidget::startTimer(int timerID, int timeinterval) {
  auto newTimer = new IntTimer(this, timerID);
  connect(newTimer, SIGNAL(timeoutWithId(int)), this, SLOT(timerListener(int)));
  newTimer->start(timeinterval);
  timers[timerID] = newTimer;
}
void AclGlobalWidget::cancelTimer(int timerID) {
  auto timerToCancel = timers[timerID];
  timers.erase(timerID);
  delete timerToCancel;
}

AclGlobalWidget *pGlobalWidget;
int main(int argc,
         char **argv) {

  pApp = new QApplication(argc, argv);
  QGraphicsScene scene;
  scene.addText("Hello, world!");

  QGraphicsView view(&scene);
  Setup();
//  view.show();
  ACL_ASSERT(pMainWindow != nullptr, "You must call \"initWindow(...)\" in Main()");
  return pApp->exec();
}

void initWindow(const char title[], int left, int top, int width, int height) {
  ACL_ASSERT(pMainWindow == nullptr, "Don't call initWindow twice");
  pMainWindow = new QMainWindow();
  pGlobalWidget = new AclGlobalWidget();
  pMainWindow->setCentralWidget(pGlobalWidget);
  pMainWindow->show();
//  GtkApplication *app;
//  app = gtk_application_window_new(app);
}

void msgBox(const char title[], const char text[], int flag) {
  QMessageBox messageBox;
  messageBox.setWindowTitle(title);
  messageBox.setText(text);
  messageBox.exec();
}

void registerKeyboardEvent(KeyboardEventCallback callback) {

}
void registerCharEvent(CharEventCallback callback) {

}
void registerMouseEvent(MouseEventCallback callback) {}
void registerTimerEvent(TimerEventCallback callback) {
  pGlobalWidget->registerTimerEvent(callback);
}

void startTimer(int timerID, int timeinterval) {
  pGlobalWidget->startTimer(timerID, timeinterval);
}
void cancelTimer(int timerID) {
  pGlobalWidget->cancelTimer(timerID);
}

// Sound
void loadSound(const char *fileName, ACL_Sound *pSound) {}
void playSound(ACL_Sound soundID, int repeat) {}
void stopSound(ACL_Sound soundID) {}

// Paint
void beginPaint() {
  pGlobalWidget->beginPaint();
}
void endPaint() {
  pGlobalWidget->endPaint();
}
void clearDevice(void) {

}
int getWidth() {

}
int getHeight() {

}

// Pen
void setPenColor(ACL_Color color) {

}
void setPenWidth(int width) {

}
void setPenStyle(ACL_Pen_Style style) {

}

// Brush
void setBrushColor(ACL_Color color) {

}
void setBrushStyle(ACL_Brush_Style style) {

}

// Text
void setTextColor(ACL_Color color) {

}
void setTextBkColor(ACL_Color color) {

}
void setTextSize(int size) {

}
void setTextFont(const char *pFontName) {

}

void paintText(int x, int y, const char *pStr) {

}

void setCaretSize(int w, int h) {

}
void setCaretPos(int x, int y) {

}
void showCaret() {

}
void hideCaret() {

}

// Pixel
void putPixel(int x, int y, ACL_Color color) {}
ACL_Color getPixel(int x, int y) {}

// the Point

/// Get the X
/// \return
int getX(void) {}
///
/// \return
int getY(void) {}
void moveTo(int x, int y) {}
void moveRel(int dx, int dy) {}

// Lines and Curves
void arc(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXStartArc, int nYStartArc, int nXEndArc, int nYEndArc) {}
void line(int x0, int y0, int x1, int y1) {
  pGlobalWidget->addLine(x0, y0, x1, y1);
}
void lineTo(int nXEnd, int nYEnd) {
  pGlobalWidget->addLineTo(nXEnd, nYEnd);
}
void lineRel(int dx, int dy) {

}
void polyBezier(const POINT *lppt, int cPoints) {

}
void polyLine(const POINT *lppt, int cPoints) {

}

// Filled Shapes
void chrod(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2) {

}
void ellipse(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect) {

}
void pie(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2) {

}
void polygon(const POINT *lpPoints, int nCount) {

}
void rectangle(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect) {

}
void roundrect(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nWidth, int nHeight) {

}

// Image
void loadImage(const char *pImageFileName, ACL_Image *pImage) {

}
void freeImage(ACL_Image *pImage) {

}

void putImage(ACL_Image *pImage, int x, int y) {

}
void putImageScale(ACL_Image *pImage, int x, int y, int width, int height) {

}
void putImageTransparent(ACL_Image *pImage, int x, int y, int width, int height, ACL_Color bkColor) {

}


void initConsole(void) {

}
