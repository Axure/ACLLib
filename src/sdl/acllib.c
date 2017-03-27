//
// Created by zhenghu on 16-7-2.
//
#include "acllib.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//The window we'll be rendering to
SDL_Window *window = NULL;
SDL_Renderer *gRenderer;
SDL_GLContext *gContext;

TimerEventCallback timerEventCallback;

int main(int argc,
         char **argv) {

  Setup();
  //Get window surface
//      screenSurface = SDL_GetWindowSurface(window);
//
//      //Fill the surface white
//      SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
//
//      //Update the surface
//      SDL_UpdateWindowSurface(window);

  //Wait two seconds
//      SDL_Delay(2000);

  //Main loop flag
  bool quit = false;
  //Event handler
  printf("Doing\n");
  SDL_Event event;
////While application is running
//  //Clear screen
//Render red filled quad
//  SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
//  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
//  SDL_RenderFillRect(gRenderer, &fillRect);
//  //Render green outlined quad
//  SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
//  SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
//  SDL_RenderDrawRect(gRenderer, &outlineRect);
//  //Draw blue horizontal line
//  SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
//  SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
//  for (int i = 0; i < SCREEN_HEIGHT; i += 4) {
//    SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
//  }

  //Update screen
  SDL_RenderPresent(gRenderer);
  while (!quit) {
    //Handle events on queue
    while (SDL_PollEvent(&event) != 0) {
      //User requests quit
      if (event.type == SDL_QUIT) {
        quit = true;
      }
      switch (event.type) {
        case SDL_USEREVENT: {
          if (event.user.data1!= NULL) {
            void (*p) (void*) = event.user.data1;
            p(event.user.data2);
          }
          break;

        }
      }
    }

//    SDL_GL_SwapWindow(window);
  }

  return 0;
}

void initWindow(const char title[], int left, int top, int width, int height) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    //Create window
    window = SDL_CreateWindow(title,
                              left,
                              top,
                              width,
                              height,
                              SDL_WINDOW_OPENGL);
    gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      exit(-1);
    };
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
  } //Destroy window

}
void msgBox(const char title[], const char text[], int flag) {

}

// Sound
void loadSound(const char *fileName, ACL_Sound *pSound) {}
void playSound(ACL_Sound soundID, int repeat) {}
void stopSound(ACL_Sound soundID) {}

int getWidth() {}
int getHeight() {}

// Pen
void setPenColor(ACL_Color color) {}
void setPenWidth(int width) {}
void setPenStyle(ACL_Pen_Style style) {}

// Brush
void setBrushColor(ACL_Color color) {}
void setBrushStyle(ACL_Brush_Style style) {}

// Text
void setTextColor(ACL_Color color) {}
void setTextBkColor(ACL_Color color) {}
void setTextSize(int size) {}
void setTextFont(const char *pFontName) {}

void paintText(int x, int y, const char *pStr) {}

void setCaretSize(int w, int h) {}
void setCaretPos(int x, int y) {}
void showCaret() {}
void hideCaret() {}

// Image
void loadImage(const char *pImageFileName, ACL_Image *pImage) {}
void freeImage(ACL_Image *pImage) {}

void putImage(ACL_Image *pImage, int x, int y) {}
void putImageScale(ACL_Image *pImage, int x, int y, int width, int height) {}
void putImageTransparent(ACL_Image *pImage, int x, int y, int width, int height, ACL_Color bkColor) {}


void initConsole(void) {}
