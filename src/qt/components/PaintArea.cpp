//
// Created by Colliot on 2016/9/6.
//

#include <cassert>
#include "PaintArea.h"
#include "MouseTranslator.h"
#include "../verdigris/src/wobjectimpl.h"
#include "functionalities/events.h"

W_OBJECT_IMPL(AclGlobalWidget)
/// Handle mouse press events.
/// \param event
void AclGlobalWidget::mousePressEvent(QMouseEvent *event) {
  if (mouseEventCallback != nullptr) {
    mouseEventCallback(event->x(), event->y(),
                       buttonFromQt(event->button()),
                       BUTTON_DOWN
    );
  }
}

void AclGlobalWidget::mouseReleaseEvent(QMouseEvent *event) {
  if (mouseEventCallback != nullptr) {
    mouseEventCallback(event->x(), event->y(),
                       buttonFromQt(event->button()),
                       BUTTON_UP
    );
  }
}

void AclGlobalWidget::mouseDoubleClickEvent(QMouseEvent *event) {
  if (mouseEventCallback != nullptr) {
    mouseEventCallback(event->x(), event->y(),
                       buttonFromQt(event->button()),
                       BUTTON_DOUBLECLICK
    );
  }
}

void AclGlobalWidget::mouseMoveEvent(QMouseEvent *event) {
  if (mouseEventCallback != nullptr) {
    mouseEventCallback(event->x(), event->y(),
                       MOUSEMOVE,
                       MOUSEMOVE
    );
  }
}

void AclGlobalWidget::wheelEvent(QWheelEvent *event) {
  if (mouseEventCallback != nullptr) {
    mouseEventCallback(event->x(), event->y(),
                       MIDDLE_BUTTON,
                       event->delta() >= 0 ? ROLL_DOWN : ROLL_UP
    );
  }
}

/**
 * The constructor of the widget.
 * Set the current point to (0, 0)
 * @return
 */
AclGlobalWidget::AclGlobalWidget()
    : currentPoint(new Point(0, 0)),
      qPen(QColor(0, 0, 0), Qt::SolidPattern),
      qBrush(QColor(0, 0, 0), Qt::SolidPattern) {
  qPen.setWidth(1);
  setMouseTracking(true);
}
AclGlobalWidget::~AclGlobalWidget() {
  delete timer;
  delete currentPoint;
}

/**
 * Delates the painter creation and choice of pen/brush.
 * Checks if the `painter` pointer is null. If not, delete it.
 * As the library provides no mutlitheading, this should be considered safe.
 * @return A pointer to the painter object.
 */
QPainter *AclGlobalWidget::getPainter() {
  assert(painter != nullptr);
  painter->setBrush(qBrush);
  painter->setPen(qPen);
  return painter;
}

/**
 * Get the X coordinate of the current point.
 * @return
 */
int AclGlobalWidget::getX(void) {
  return currentPoint->x;
}
int AclGlobalWidget::getY(void) {
  return currentPoint->y;
}
void AclGlobalWidget::moveTo(int x, int y) {
  currentPoint->x = x;
  currentPoint->y = y;
}
void AclGlobalWidget::moveRel(int dx, int dy) {
  currentPoint->x += dx;
  currentPoint->y += dy;
}

void AclGlobalWidget::addLine(int startX, int startY, int endX, int endY) {
  getPainter()->drawLine(startX, startY, endX, endY);
}

void AclGlobalWidget::addLineTo(int endX, int endY) {
  getPainter()->drawLine(currentPoint->x, currentPoint->y, endX, endY);
}

void AclGlobalWidget::lineRel(int dx, int dy) {
  getPainter()->drawLine(currentPoint->x, currentPoint->y,
                   currentPoint->x + dx, currentPoint->y + dy);
}
void AclGlobalWidget::polyBezier(const POINT *lppt, int cPoints) {

}
void AclGlobalWidget::polyLine(const POINT *lppt, int cPoints) {

}

// Filled Shapes
void AclGlobalWidget::chrod(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2) {

}
void AclGlobalWidget::ellipse(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect) {
  getPainter()->drawEllipse(nLeftRect, nTopRect, nRightRect, nBottomRect);
}
void AclGlobalWidget::pie(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2) {

}
void AclGlobalWidget::polygon(const POINT *lpPoints, int nCount) {

}
void AclGlobalWidget::rectangle(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect) {
  getPainter()->drawRect(nLeftRect, nTopRect, nRightRect - nLeftRect, nBottomRect - nTopRect);
}
void AclGlobalWidget::roundrect(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nWidth, int nHeight) {

}


void AclGlobalWidget::keyPressEvent(QKeyEvent *event) {
  qDebug() << "Key " << event->key() << " pressed";
  if (keyboardEventCallback != nullptr) {
    keyboardEventCallback(keyboardTranslator.fromQtKeyCode(event->key()), KEY_DOWN);
  }
}

void AclGlobalWidget::keyReleaseEvent(QKeyEvent *event) {
  qDebug() << "Key " << event->key() << " released";
  if (keyboardEventCallback != nullptr) {
    keyboardEventCallback(keyboardTranslator.fromQtKeyCode(event->key()), KEY_UP);
  }
}

void AclGlobalWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QRect dirtyRect = event->rect();
  painter.drawImage(dirtyRect, image, dirtyRect);
//  painter.setRenderHints(QPainter::HighQualityAntialiasing, true);
}

void AclGlobalWidget::resizeEvent(QResizeEvent *event)
{
  if (width() > image.width() || height() > image.height()) {
    int newWidth = qMax(width() + 128, image.width());
    int newHeight = qMax(height() + 128, image.height());
    resizeImage(&image, QSize(newWidth, newHeight));
    update();
  }
  QWidget::resizeEvent(event);
}

void AclGlobalWidget::resizeImage(QImage *image, const QSize &newSize)
//! [19] //! [20]
{
  if (image->size() == newSize)
    return;

  QImage newImage(newSize, QImage::Format_RGB32);
  newImage.fill(qRgb(255, 255, 255));
  QPainter painter(&newImage);
  painter.drawImage(QPoint(0, 0), *image);
  *image = newImage;
}

void AclGlobalWidget::timerListener(int timerId) {
  if (timerEventCallback != nullptr) {
    timerEventCallback(timerId);
  }
}

void AclGlobalWidget::beginPaint() {
  painter = new QPainter(&image);
}
void AclGlobalWidget::endPaint() {
  update();
  if (painter) delete painter;
}
void AclGlobalWidget::clearDevice(void) {
  image.fill(qRgb(255, 255, 255));
}
int AclGlobalWidget::getWidth() {
  return width();
}
int AclGlobalWidget::getHeight() {
  return height();
}

void AclGlobalWidget::registerTimerEvent(TimerEventCallback callback) {
  timerEventCallback = callback;
}

void AclGlobalWidget::registerKeyboardEvent(KeyboardEventCallback callback) {
  keyboardEventCallback = callback;
}

void AclGlobalWidget::registerCharEvent(CharEventCallback callback) {
  charEventCallback = callback;
}
void AclGlobalWidget::registerMouseEvent(MouseEventCallback callback) {
  mouseEventCallback = callback;
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
QPen &AclGlobalWidget::getQPen() {
  return qPen;
}
QBrush &AclGlobalWidget::getQBrush() {
  return qBrush;
}
