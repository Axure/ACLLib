//
// Created by Colliot on 2016/9/6.
//

#ifndef PROJECT_PAINTAREA_H
#define PROJECT_PAINTAREA_H

#include <acllib.h>

#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

#include <QPen>
#include <QBrush>
#include <QRect>
#include <QMouseEvent>
#include <deque>
#include <map>
#include "../verdigris/src/wobjectdefs.h"
#include <QtWidgets/QMessageBox>

#include "IntTimer.h"
#include "KeyboardTranslator.h"

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
};

// TODO: a bridge between ACL types and platform/framework types.

/**
 *
 */
class AclGlobalWidget: public QWidget {
  W_OBJECT(AclGlobalWidget)
 private:
  KeyboardTranslator keyboardTranslator;
  QPainter *painter = nullptr;
  QImage image;
  QPen qPen;
  QBrush qBrush;
  std::string title;
  Point *currentPoint;
  QTimer *timer;
  std::map<int, IntTimer *> timers;
  TimerEventCallback timerEventCallback = nullptr;
  CharEventCallback charEventCallback = nullptr;
  MouseEventCallback mouseEventCallback = nullptr;
  KeyboardEventCallback keyboardEventCallback = nullptr;
 private:
  /**
   * Delates the painter creation and choice of pen/brush.
   * @return A pointer to the painter object.
   */
  QPainter *getPainter();
 protected:
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  void paintEvent(QPaintEvent *event);
  void resizeEvent(QResizeEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseDoubleClickEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);
  void resizeImage(QImage *image, const QSize &newSize);
  /**
   * A slot handling the timers based on the ID.
   * @param timerId
   */
  void timerListener(int timerId);
  W_SLOT(timerListener)
 public:
  AclGlobalWidget();
  ~AclGlobalWidget();

  //
  int getX(void);
  int getY(void);
  void moveTo(int x, int y);
  void moveRel(int dx, int dy);
  ///
  void addLine(int startX, int startY, int endX, int endY);
  void addLineTo(int endX, int endY);
  void lineRel(int dx, int dy);
  void polyBezier(const POINT *lppt, int cPoints);
  void polyLine(const POINT *lppt, int cPoints);
  void chrod(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2);
  void ellipse(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);
  void pie(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2);
  void polygon(const POINT *lpPoints, int nCount);
  void rectangle(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);
  void roundrect(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nWidth, int nHeight);
  ///
  void beginPaint();
  void endPaint();
  void clearDevice(void);
  int getWidth();
  int getHeight();
  void registerTimerEvent(TimerEventCallback callback);
  void registerKeyboardEvent(KeyboardEventCallback callback);
  void registerCharEvent(CharEventCallback callback);
  void registerMouseEvent(MouseEventCallback callback);
  void startTimer(int timerID, int timeinterval);
  void cancelTimer(int timerID);
 public:
  QPen &getQPen();
  QBrush &getQBrush();
};


#endif //PROJECT_PAINTAREA_H
