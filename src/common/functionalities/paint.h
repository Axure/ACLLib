#ifndef PROJECT_PAINT_H
#define PROJECT_PAINT_H

#include "../definitions/color.h"
typedef struct tagPOINT POINT,*PPOINT,*NPPOINT,*LPPOINT;

//
//typedef struct {
//
//} HBITMAP;
//
//typedef struct {
//
//} POINT;
//
//typedef struct {
//
//} COLORREF;

typedef enum {
  PEN_STYLE_SOLID,
  PEN_STYLE_DASH, /* -------  */
  PEN_STYLE_DOT, /* .......  */
  PEN_STYLE_DASHDOT, /* _._._._  */
  PEN_STYLE_DASHDOTDOT, /* _.._.._  */
  PEN_STYLE_NULL
} ACL_Pen_Style;

typedef enum {
  BRUSH_STYLE_SOLID = -1,
  BRUSH_STYLE_HORIZONTAL, /* ----- */
  BRUSH_STYLE_VERTICAL, /* ||||| */
  BRUSH_STYLE_FDIAGONAL, /* \\\\\ */
  BRUSH_STYLE_BDIAGONAL, /* ///// */
  BRUSH_STYLE_CROSS, /* +++++ */
  BRUSH_STYLE_DIAGCROSS, /* xxxxx */
  BRUSH_STYLE_NULL
} ACL_Brush_Style;


// Paint
void beginPaint();
void endPaint();
void clearDevice(void);
int getWidth();
int getHeight();

// Pen
void setPenColor(ACL_Color color);
void setPenWidth(int width);
void setPenStyle(ACL_Pen_Style style);

// Brush
void setBrushColor(ACL_Color color);
void setBrushStyle(ACL_Brush_Style style);

// Pixel
void putPixel(int x, int y, ACL_Color color);
ACL_Color getPixel(int x, int y);

// the Point
int getX(void);
int getY(void);
void moveTo(int x, int y);
void moveRel(int dx, int dy);

// Lines and Curves
void arc(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXStartArc, int nYStartArc, int nXEndArc, int nYEndArc);
void line(int x0, int y0, int x1, int y1);
void lineTo(int nXEnd, int nYEnd);
void lineRel(int dx, int dy);
void polyBezier(const POINT *lppt, int cPoints);
void polyLine(const POINT *lppt, int cPoints);

// Filled Shapes
void chrod(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2);
///
/// \param nLeftRect
/// \param nTopRect
/// \param nRightRect
/// \param nBottomRect
void ellipse(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);
///
/// \param nLeftRect
/// \param nTopRect
/// \param nRightRect
/// \param nBottomRect
/// \param nXRadial1
/// \param nYRadial1
/// \param nXRadial2
/// \param nYRadial2
void pie(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2);
///
/// \param lpPoints
/// \param nCount
void polygon(const POINT *lpPoints, int nCount);
///
/// \param nLeftRect
/// \param nTopRect
/// \param nRightRect
/// \param nBottomRect
void rectangle(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);
///
/// \param nLeftRect
/// \param nTopRect
/// \param nRightRect
/// \param nBottomRect
/// \param nWidth
/// \param nHeight
void roundrect(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nWidth, int nHeight);


#ifdef _UNICODE
#undef _UNICODE
#endif
#ifdef UNICODE
#undef UNICODE
#endif
// Text
void setTextColor(ACL_Color color);
void setTextBkColor(ACL_Color color);
void setTextSize(int size);
void setTextFont(const char *pFontName);

void paintText(int x, int y, const char *pStr);

void setCaretSize(int w, int h);
void setCaretPos(int x, int y);
void showCaret();
void hideCaret();

#endif //PROJECT_PAINT_H
