//
// Created by zhenghu on 16-7-25.
//
extern "C" {
#include "acllib.h"
}

#include "../components/PaintArea.h"
#include "../window.h"

int getRValue(COLORREF color) {
  return (int) (color & 255);
}
int getGValue(COLORREF color) {
  return (int) ((color >> 8) & 255);
}

int getBValue(COLORREF color) {
  return (int) ((color >> 16) & 255);
}

#ifdef _DEBUG
#define ACL_ASSERT(_Expression,errStr) (void)( (!!(_Expression)) || (acl_error(errStr),0) )
#else
#define ACL_ASSERT(flag, errStr) ((void)0)
#endif
#define ACL_ASSERT_HWND ACL_ASSERT(pApp!=0, \
    "You should call function \"initWindow(...)\" befor use function \"" __FUNCTION__ "\"" )

QApplication *pApp;
QMainWindow *pMainWindow;

AclGlobalWidget *pGlobalWidget;

void acl_error(char *errStr) {

  msgBox("Error!", errStr, NULL);
  exit(0);
}

int main(int argc,
         char **argv) {

  pApp = new QApplication(argc, argv);
  QGraphicsScene scene;
  scene.addText("Hello, world!");

  QGraphicsView view(&scene);
  Setup();
//  view.show();
  return pApp->exec();
}


void registerKeyboardEvent(KeyboardEventCallback callback) {
  pGlobalWidget->registerKeyboardEvent(callback);
}
void registerCharEvent(CharEventCallback callback) {
  pGlobalWidget->registerCharEvent(callback);
}
void registerMouseEvent(MouseEventCallback callback) {
  pGlobalWidget->registerMouseEvent(callback);
}

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
  pGlobalWidget->clearDevice();
}
int getWidth() {

}
int getHeight() {

}

// Pen
void setPenColor(ACL_Color color) {
  auto r = getRValue(color);
  auto g = getGValue(color);
  auto b = getBValue(color);
  pGlobalWidget->getQPen().setColor(QColor(r, g, b));
}
void setPenWidth(int width) {
  pGlobalWidget->getQPen().setWidth(width);
}
void setPenStyle(ACL_Pen_Style style) {

}

// Brush
void setBrushColor(ACL_Color color) {
  auto r = getRValue(color);
  auto g = getGValue(color);
  auto b = getBValue(color);
  pGlobalWidget->getQBrush().setColor(QColor(r, g, b));
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
void moveTo(int x, int y) {
  pGlobalWidget->moveTo(x, y);
}
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
  pGlobalWidget->lineRel(dx, dy);
}
void polyBezier(const POINT *lppt, int cPoints) {
  pGlobalWidget->polyBezier(lppt, cPoints);
}
void polyLine(const POINT *lppt, int cPoints) {
  pGlobalWidget->polyLine(lppt, cPoints);
}

// Filled Shapes
void chrod(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2) {
  pGlobalWidget->chrod(nLeftRect, nTopRect, nRightRect, nBottomRect, nXRadial1, nYRadial1, nXRadial2, nYRadial2);
}
void ellipse(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect) {
  pGlobalWidget->ellipse(nLeftRect, nTopRect, nRightRect - nLeftRect, nBottomRect - nTopRect);
}
void pie(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2) {
  pGlobalWidget->pie(nLeftRect, nTopRect, nRightRect, nBottomRect, nXRadial1, nYRadial1, nXRadial2, nYRadial2);
}
void polygon(const POINT *lpPoints, int nCount) {
  pGlobalWidget->polygon(lpPoints, nCount);
}
void rectangle(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect) {
  pGlobalWidget->rectangle(nLeftRect, nTopRect, nRightRect, nBottomRect);
}
void roundrect(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nWidth, int nHeight) {
  pGlobalWidget->roundrect(nLeftRect, nTopRect, nRightRect, nBottomRect, nWidth, nHeight);
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
