//
// Created by Colliot on 2016/9/6.
//
#include "../global.h"
#include "functionalities/paint.h"
#include <windows.h>

extern HWND g_hWnd;

HDC g_hmemdc = NULL;
HBITMAP g_HBITMAP = NULL;


HPEN g_pen = NULL;
ACL_Color g_penColor = BLACK;
int g_penWidth = 1;
int g_penStyle = PEN_STYLE_SOLID;

HBRUSH g_brush = NULL;
ACL_Color g_brushColor = BLACK;
int g_brushStyle = BRUSH_STYLE_SOLID;

HFONT g_font = NULL;
char g_fontName[256] = "宋体";
int g_textSize = 12;
ACL_Color g_textColor = BLACK;
ACL_Color g_textBkColor = WHITE;

int g_caretHeight = 12;
int g_caretWidth = 6;
int g_caretX = 0;
int g_caretY = 0;



//
void updatePen();
void updateBrush();
void updateFont();

//
void beginPaint() {
  HDC hdc;

  ACL_ASSERT_HWND;

  hdc = GetDC(g_hWnd);
  g_hmemdc = CreateCompatibleDC(hdc);
  SelectObject(g_hmemdc, g_HBITMAP);

  updatePen();
  updateBrush();
  updateFont();
  setTextColor(g_textColor);
  setTextBkColor(g_textBkColor);
}

void endPaint() {
  DeleteDC(g_hmemdc);
  g_hmemdc = 0;
  InvalidateRect(g_hWnd, 0, 0);

  DeleteObject(g_pen);
  DeleteObject(g_brush);
  DeleteObject(g_font);
  g_pen = NULL;
  g_brush = NULL;
  g_font = NULL;
}

void clearDevice(void) {
  ACL_ASSERT_BEGIN_PAINT;
  BitBlt(
      g_hmemdc,
      0, 0,
      GetSystemMetrics(SM_CXSCREEN),
      GetSystemMetrics(SM_CYSCREEN),
      g_hmemdc,
      0, 0,
      WHITENESS);
}

void updatePen() {
  if (g_pen)DeleteObject(g_pen);
  if (g_penColor == EMPTY)
    g_pen = (HPEN) GetStockObject(NULL_PEN);
  else
    g_pen = CreatePen(g_penStyle, g_penWidth, g_penColor);
  SelectObject(g_hmemdc, g_pen);
}

void updateBrush() {
  if (g_brush)DeleteObject(g_brush);
  if (g_brushColor == EMPTY) {
    g_brush = (HBRUSH) GetStockObject(NULL_BRUSH);
  }
  else {
    if (g_brushStyle == BRUSH_STYLE_SOLID)
      g_brush = CreateSolidBrush(g_brushColor);
    else
      g_brush = CreateHatchBrush(g_brushStyle, g_brushColor);
  }
  SelectObject(g_hmemdc, g_brush);
}

void updateFont() {
  if (g_font)DeleteObject(g_font);
  g_font = CreateFontA(
      g_textSize,
      0,
      0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, g_fontName);
  SelectObject(g_hmemdc, g_font);
}

void setPenColor(ACL_Color newColor) {
  ACL_ASSERT_BEGIN_PAINT;
  g_penColor = newColor;
  updatePen();
}

void setPenWidth(int width) {
  ACL_ASSERT_BEGIN_PAINT;
  g_penWidth = width;
  updatePen();
}

void setPenStyle(ACL_Pen_Style newStyle) {
  ACL_ASSERT_BEGIN_PAINT;

  switch (newStyle) {
    case PEN_STYLE_SOLID:
      g_penStyle = PS_SOLID;
      break;
    case PEN_STYLE_DASH:
      g_penStyle = PS_DASH;
      break;
    case PEN_STYLE_DOT:
      g_penStyle = PS_DOT;
      break;
    case PEN_STYLE_DASHDOT:
      g_penStyle = PS_DASHDOT;
      break;
    case PEN_STYLE_DASHDOTDOT:
      g_penStyle = PS_DASHDOTDOT;
      break;
    case PEN_STYLE_NULL:
      g_penStyle = -1;
      setPenColor(EMPTY);
      return;
    default:
      break;
  }
  updatePen();
}

void setBrushColor(ACL_Color newColor) {
  ACL_ASSERT_BEGIN_PAINT;
  g_brushColor = newColor;
  updateBrush();
}

void setBrushStyle(ACL_Brush_Style newStyle) {
  ACL_ASSERT_BEGIN_PAINT;

  switch (newStyle) {
    case BRUSH_STYLE_SOLID:
      g_brushStyle = BRUSH_STYLE_SOLID;
      break;
    case BRUSH_STYLE_HORIZONTAL:
      g_brushStyle = HS_HORIZONTAL;
      break;
    case BRUSH_STYLE_VERTICAL:
      g_brushStyle = HS_VERTICAL;
      break;
    case BRUSH_STYLE_FDIAGONAL:
      g_brushStyle = HS_FDIAGONAL;
      break;
    case BRUSH_STYLE_BDIAGONAL:
      g_brushStyle = HS_BDIAGONAL;
      break;
    case BRUSH_STYLE_CROSS:
      g_brushStyle = HS_CROSS;
      break;
    case BRUSH_STYLE_DIAGCROSS:
      g_brushStyle = HS_DIAGCROSS;
      break;
    case BRUSH_STYLE_NULL:
      g_brushStyle = BRUSH_STYLE_SOLID;
      setBrushColor(EMPTY);
      return;
    default:
      break;
  }
  updateBrush();
}


void putPixel(int x, int y, ACL_Color color) {
  ACL_ASSERT_BEGIN_PAINT;
  SetPixel(g_hmemdc, x, y, color);
}

ACL_Color getPixel(int x, int y) {
  ACL_ASSERT_BEGIN_PAINT;
  return GetPixel(g_hmemdc, x, y);
}

int getWidth(void) {
  RECT rect;
  GetClientRect(g_hWnd, &rect);
  return rect.right;
}

int getHeight(void) {
  RECT rect;
  GetClientRect(g_hWnd, &rect);
  return rect.bottom;
}

int getX(void) {
  POINT point;
  ACL_ASSERT_BEGIN_PAINT;
  GetCurrentPositionEx(g_hmemdc, &point);
  return (int) point.x;
}

int getY(void) {
  POINT point;
  ACL_ASSERT_BEGIN_PAINT;
  GetCurrentPositionEx(g_hmemdc, &point);
  return (int) point.y;
}

void moveTo(int x, int y) {
  ACL_ASSERT_BEGIN_PAINT;
  MoveToEx(g_hmemdc, x, y, NULL);
}

void moveRel(int dx, int dy) {
  POINT point;
  ACL_ASSERT_BEGIN_PAINT;
  GetCurrentPositionEx(g_hmemdc, &point);
  MoveToEx(g_hmemdc, (int) point.x + dx, (int) point.y + dy, NULL);
}

// Lines and Curves
void arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
  ACL_ASSERT_BEGIN_PAINT;
  Arc(g_hmemdc, x1, y1, x2, y2, x3, y3, x4, y4);
}

void line(int x0, int y0, int x1, int y1) {
  POINT point;
  ACL_ASSERT_BEGIN_PAINT;
  GetCurrentPositionEx(g_hmemdc, &point);
  MoveToEx(g_hmemdc, x0, y0, NULL);
  LineTo(g_hmemdc, x1, y1);
  MoveToEx(g_hmemdc, point.x, point.y, NULL);
}

void lineTo(int x, int y) {
  ACL_ASSERT_BEGIN_PAINT;
  LineTo(g_hmemdc, x, y);
}

void lineRel(int dx, int dy) {
  POINT point;
  ACL_ASSERT_BEGIN_PAINT;
  GetCurrentPositionEx(g_hmemdc, &point);
  LineTo(g_hmemdc, (int) point.x + dx, (int) point.y + dy);
}

void polyBezier(const POINT *lppt, int cPoints) {
  PolyBezier(g_hmemdc, lppt, cPoints);
}

void polyLine(const POINT *lppt, int cPoints) {
  Polyline(g_hmemdc, lppt, cPoints);
}

// Filled Shapes
void chrod(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
  ACL_ASSERT_BEGIN_PAINT;
  Chord(g_hmemdc, x1, y1, x2, y2, x3, y3, x4, y4);
}

void ellipse(int left, int top, int right, int bottom) {
  ACL_ASSERT_BEGIN_PAINT;
  Ellipse(g_hmemdc, left, top, right, bottom);
}

void pie(int left, int top, int right, int bottom, int xr1, int yr1, int xr2, int yr2) {
  ACL_ASSERT_BEGIN_PAINT;
  Pie(g_hmemdc, left, top, right, bottom, xr1, yr1, xr2, yr2);
}

void polygon(const POINT *apt, int cpt) {
  ACL_ASSERT_BEGIN_PAINT;
  Polygon(g_hmemdc, apt, cpt);
}

void rectangle(int left, int top, int right, int bottom) {
  ACL_ASSERT_BEGIN_PAINT;
  Rectangle(g_hmemdc, left, top, right, bottom);
}

void roundrect(int left, int top, int right, int bottom, int width, int height) {
  ACL_ASSERT_BEGIN_PAINT;
  RoundRect(g_hmemdc, left, top, right, bottom, width, height);
}

void polyline(POINT *apt, int cpt) {
  ACL_ASSERT_BEGIN_PAINT;
  Polyline(g_hmemdc, apt, cpt);
}


void setTextColor(ACL_Color color) {
  ACL_ASSERT_BEGIN_PAINT;
  ACL_ASSERT(color != EMPTY, "text color can not be EMPTY");
  g_textColor = color;
  SetTextColor(g_hmemdc, color);
}

void setTextBkColor(ACL_Color color) {
  ACL_ASSERT_BEGIN_PAINT;
  g_textBkColor = color;
  if (color == EMPTY)
    SetBkMode(g_hmemdc, TRANSPARENT);
  else {
    SetBkMode(g_hmemdc, OPAQUE);
    SetBkColor(g_hmemdc, color);
  }
}

void setTextSize(int size) {
  ACL_ASSERT_BEGIN_PAINT;
  g_textSize = size;
  updateFont();
}

void setTextFont(const char *pfn) {
  size_t len;
  ACL_ASSERT_BEGIN_PAINT;
  len = strlen(pfn);
  strcpy(g_fontName, pfn);
  updateFont();
}

void paintText(int x, int y, const char *textstring) {
  ACL_ASSERT_BEGIN_PAINT;
  TextOutA(g_hmemdc, x, y, textstring, strlen(textstring));
}

void setCaretSize(int w, int h) {
  DestroyCaret();
  CreateCaret(g_hWnd, 0, w, h);
  SetCaretPos(g_caretX, g_caretY);
}

void setCaretPos(int x, int y) {
  g_caretX = x;
  g_caretY = y;
  SetCaretPos(g_caretX, g_caretY);
}

void showCaret() {
  ShowCaret(g_hWnd);
}

void hideCaret() {
  HideCaret(g_hWnd);
}