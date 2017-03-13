//
// Created by zhenghu on 16-9-10.
//

#include <SDL.h>
#include "functionalities/paint.h"
#include "../SDL2_gfx/SDL2_gfxPrimitives.h"
extern SDL_Window *window;
extern SDL_Renderer *gRenderer;
extern SDL_GLContext *gContext;

int current_x = 0, current_y = 0;
// Paint
void beginPaint() {
//  gRenderer = gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
void endPaint() {
  SDL_RenderPresent(gRenderer);
//  free(gRenderer);
}
void clearDevice(void) {
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
}

// Pixel
void putPixel(int x, int y, ACL_Color color) {}
ACL_Color getPixel(int x, int y) {}

// the Point
int getX(void) {}
int getY(void) {}
void moveTo(int x, int y) {
  current_x = x;
  current_y = y;
}
void moveRel(int dx, int dy) {
  current_x += dx;
  current_y += dy;
}

// Lines and Curves
void arc(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXStartArc, int nYStartArc, int nXEndArc, int nYEndArc) {}
void line(int x0, int y0, int x1, int y1) {}
void lineTo(int nXEnd, int nYEnd) {
  lineRGBA(gRenderer, current_x, current_y, nXEnd, nYEnd, 100, 50, 123, 255);
}
void lineRel(int dx, int dy) {}
void polyBezier(const POINT *lppt, int cPoints) {}
void polyLine(const POINT *lppt, int cPoints) {}

// Filled Shapes
void chrod(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2) {}
void ellipse(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect) {
//  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  printf("rendered ellipse!\n");
  ellipseRGBA(gRenderer,
              (nRightRect + nLeftRect) / 2,
              (nBottomRect + nTopRect) / 2,
              (nRightRect - nLeftRect) / 2,
              (nBottomRect - nTopRect) / 2,
              50, 100, 100,
              255);
//  SDL_RenderClear( gRenderer );
}
void pie(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2) {}
void polygon(const POINT *lpPoints, int nCount) {}
void rectangle(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect) {}
void roundrect(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nWidth, int nHeight) {}
