//
// Created by zhenghu on 16-7-2.
//
#include "../common/acllib.h"

#include <SDL.h>
#include <SDL_opengl.h>

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
//  SDL_DestroyWindow(window);

  //Quit SDL subsystems
//  SDL_Quit();

  return 0;
  return 0;
}
void DrawEllipse(float cx, float cy, float rx, float ry, int num_segments) {
  float theta = 2 * 3.1415926 / (float)(num_segments);
  float c = cosf(theta);//precalculate the sine and cosine
  float s = sinf(theta);
  float t;

  float x = 1;//we start at angle = 0
  float y = 0;

  glBegin(GL_LINE_LOOP);
  glColor3f(1.0f, 0.0f, 0.0f); // Red
  for (int ii = 0; ii < num_segments; ii++) {
    //apply radius and offset
    glVertex2f(x * rx + cx, y * ry + cy);//output vertex
    printf("%f, %f\n", x * rx + cx, y * ry + cy);
    //apply the rotation matrix
    t = x;
    x = c * x - s * y;
    y = s * t + c * y;
  }
  glEnd();
}

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar) {

  GLdouble fW, fH;

  fH = tan(fovY / 360 * M_PI) * zNear;
  fW = fH * aspect;

  glFrustum(-fW, fW, -fH, fH, zNear, zFar);

}
/* function to reset our viewport after a window resize */
int Display_SetViewport(int width, int height) {

  /* Height / width ration */
  GLfloat ratio;

  /* Protect against a divide by zero */
  if (height == 0) {
    height = 1;
  }

  ratio = (GLfloat) width / (GLfloat) height;

  /* Setup our viewport. */
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);

  /* change to the projection matrix and set our viewing volume. */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  /* Set our perspective */
  perspectiveGL(45.0f, ratio, 0.1f, 100.0f);

  /* Make sure we're chaning the model view and not the projection */
  glMatrixMode(GL_MODELVIEW);

  /* Reset The View */
  glLoadIdentity();

  return 1;
}

void Display_Render() {
//  /* Set the background black */
//  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
//  /* Clear The Screen And The Depth Buffer */
//  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//
//  /* Move Left 1.5 Units And Into The Screen 6.0 */
//  glLoadIdentity();
  glTranslatef(-1.5f, 0.0f, -6.0f);
  // Draw a Red 1x1 Square centered at origin
  glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
  glColor3f(1.0f, 0.0f, 0.0f); // Red
  glVertex2f(-0.5f, -0.5f);    // x, y
  glVertex2f( 0.5f, -0.5f);
  glVertex2f( 0.5f,  0.5f);
  glVertex2f(-0.5f,  0.5f);
  glEnd();
//  glBegin(GL_TRIANGLES);            /* Drawing Using Triangles */
//  glVertex3f(0.0f, 1.0f, 0.0f); /* Top */
//  glVertex3f(-1.0f, -1.0f, 0.0f); /* Bottom Left */
//  glVertex3f(1.0f, -1.0f, 0.0f); /* Bottom Right */
//  glEnd();                           /* Finished Drawing The Triangle */
//
//  /* Move Right 3 Units */
//  glTranslatef(3.0f, 0.0f, 0.0f);
//
//  glBegin(GL_QUADS);                /* Draw A Quad */
//  glVertex3f(-1.0f, 1.0f, 0.0f); /* Top Left */
//  glVertex3f(1.0f, 1.0f, 0.0f); /* Top Right */
//  glVertex3f(1.0f, -1.0f, 0.0f); /* Bottom Right */
//  glVertex3f(-1.0f, -1.0f, 0.0f); /* Bottom Left */
//  glEnd();                           /* Done Drawing The Quad */

}
bool initGL() {
  bool success = true;
  GLenum error = GL_NO_ERROR;

  //Initialize Projection Matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //Check for error
  error = glGetError();
  if (error != GL_NO_ERROR) {
    success = false;
  }

  //Initialize Modelview Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //Check for error
  error = glGetError();
  if (error != GL_NO_ERROR) {
    success = false;
  }

  //Initialize clear color
  glClearColor(0.f, 0.f, 0.f, 1.f);

  //Check for error
  error = glGetError();
  if (error != GL_NO_ERROR) {
    success = false;
  }

  return success;
}
void initWindow(const char title[], int left, int top, int width, int height) {

  // The surface contained by the window
  SDL_Surface *screenSurface = NULL; //Initialize SD
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    //Create window
    window = SDL_CreateWindow(title,
                              left,
                              top,
                              1200,
                              1200,
                              SDL_WINDOW_OPENGL);
    gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    } else {

      //Create context
      gContext = SDL_GL_CreateContext(window);
      if (gContext == NULL) {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
      } else {
        //Use Vsync
        if (SDL_GL_SetSwapInterval(1) < 0) {
          printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
        }

        //Initialize OpenGL
        if (!initGL()) {
          printf("Unable to initialize OpenGL!\n");
          exit(-1);
        }
      }
      Display_SetViewport(SCREEN_WIDTH, SCREEN_HEIGHT);
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
      SDL_Event e;
      Display_Render();
//While application is running
      //Clear screen
//      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
//      SDL_RenderClear( gRenderer );
////Render red filled quad
//      SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
//      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
//      SDL_RenderFillRect( gRenderer, &fillRect );
//      //Render green outlined quad
//      SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
//      SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
//      SDL_RenderDrawRect( gRenderer, &outlineRect );
//      //Draw blue horizontal line
//      SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
//      SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );
//      for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
//      {
//        SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
//      }
//
//      //Update screen
//      SDL_RenderPresent( gRenderer );
      while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
          //User requests quit
          if (e.type == SDL_QUIT) {
            quit = true;
          }
          switch (e.type) {

          }
        }
      }
    }
  } //Destroy window

//  GtkApplication *app;
//  app = gtk_application_window_new(app);

}
void msgBox(const char title[], const char text[], int flag) {

}

void registerKeyboardEvent(KeyboardEventCallback callback) {

}
void registerCharEvent(CharEventCallback callback) {

}
void registerMouseEvent(MouseEventCallback callback) {}
void registerTimerEvent(TimerEventCallback callback) {}

void startTimer(int timerID, int timeinterval) {

}
void cancelTimer(int timerID) {}

// Sound
void loadSound(const char *fileName, ACL_Sound *pSound) {}
void playSound(ACL_Sound soundID, int repeat) {}
void stopSound(ACL_Sound soundID) {}

// Paint
void beginPaint() {
  gRenderer = gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
void endPaint() {
  SDL_GL_SwapWindow(window);
}
void clearDevice(void) {}
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

// Pixel
void putPixel(int x, int y, ACL_Color color) {}
ACL_Color getPixel(int x, int y) {}

// the Point
int getX(void) {}
int getY(void) {}
void moveTo(int x, int y) {}
void moveRel(int dx, int dy) {}

// Lines and Curves
void arc(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXStartArc, int nYStartArc, int nXEndArc, int nYEndArc) {}
void line(int x0, int y0, int x1, int y1) {}
void lineTo(int nXEnd, int nYEnd) {}
void lineRel(int dx, int dy) {}
void polyBezier(const POINT *lppt, int cPoints) {}
void polyLine(const POINT *lppt, int cPoints) {}

// Filled Shapes
void chrod(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2) {}
void ellipse(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect) {

  DrawEllipse(1, 1, 1, 1, 200);
}
void pie(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2) {}
void polygon(const POINT *lpPoints, int nCount) {}
void rectangle(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect) {}
void roundrect(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nWidth, int nHeight) {}

// Image
void loadImage(const char *pImageFileName, ACL_Image *pImage) {}
void freeImage(ACL_Image *pImage) {}

void putImage(ACL_Image *pImage, int x, int y) {}
void putImageScale(ACL_Image *pImage, int x, int y, int width, int height) {}
void putImageTransparent(ACL_Image *pImage, int x, int y, int width, int height, ACL_Color bkColor) {}


void initConsole(void) {}
