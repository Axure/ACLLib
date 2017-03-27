//
// Created by zhenghu on 16-7-2.
//
#include "../common/acllib.h"

#include <gtk/gtk.h>
#include <assert.h>
#define G_GET(var, type, member) (((type*)var)->member)

typedef struct _window_info {
  char *title;
  int left, top, width, height;
} window_info_s;

window_info_s window_info;

gboolean
draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data)
{
  guint width, height;
  GdkRGBA color;
  GtkStyleContext *context;

  context = gtk_widget_get_style_context (widget);

  width = gtk_widget_get_allocated_width (widget);
  height = gtk_widget_get_allocated_height (widget);

  gtk_render_background (context, cr, 0, 0, width, height);

  cairo_arc (cr,
             width / 2.0, height / 2.0,
             MIN (width, height) / 2.0,
             0, 2 * G_PI);

  gtk_style_context_get_color (context,
                               gtk_style_context_get_state (context),
                               &color);
  gdk_cairo_set_source_rgba (cr, &color);

  cairo_fill (cr);

  return FALSE;
}

static void
activate(GtkApplication *app,
         gpointer user_data) {
  GtkWidget *window;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (window), G_GET(user_data, window_info_s, title));
  gtk_window_set_default_size(
      GTK_WINDOW (window),
      G_GET(user_data, window_info_s, width),
      G_GET(user_data, window_info_s, height)
  );
  gtk_window_move(
    GTK_WINDOW(window),
    G_GET(user_data, window_info_s, left),
    G_GET(user_data, window_info_s, top)
  );

  GtkWidget *drawing_area = gtk_drawing_area_new ();
  gtk_widget_set_size_request (drawing_area, 100, 100);
  g_signal_connect (G_OBJECT (drawing_area), "draw",
                    G_CALLBACK (draw_callback), NULL);

  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
  gtk_container_add(GTK_CONTAINER(window), box);


  GtkWidget* button = gtk_button_new();

  gtk_container_add(GTK_CONTAINER(box), drawing_area);
  gtk_container_add(GTK_CONTAINER(box), button);
  gtk_widget_show_all(window);
}

int main(int argc,
         char **argv) {

  Setup();
  printf("THis is not turE!\n");

  GtkApplication *app;
  int status;


  app = gtk_application_new("edu.zju.cprogramming", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK(activate), &window_info);

  status = g_application_run(G_APPLICATION (app), argc, argv);
  g_object_unref(app);

  printf("THis is not turE!%d\n", status);
  return status;
}

void initWindow(const char title[], int left, int top, int width, int height) {
  window_info.title = (char*)title;
  window_info.left = left;
  window_info.top = top;
  window_info.height = height;
  window_info.width = width;


//  GtkApplication *app;
//  app = gtk_application_window_new(app);

}
void msgBox(const char title[], const char text[], int flag) {
  gtk_dialog_new();
}

void registerKeyboardEvent(KeyboardEventCallback callback) {

}
void registerCharEvent(CharEventCallback callback) {

}
void registerMouseEvent(MouseEventCallback callback) { }
void registerTimerEvent(TimerEventCallback callback) { }

void startTimer(int timerID, int timeinterval) { }
void cancelTimer(int timerID) { }

// Sound
void loadSound(const char *fileName, ACL_Sound *pSound) { }
void playSound(ACL_Sound soundID, int repeat) { }
void stopSound(ACL_Sound soundID) { }

// Paint
void beginPaint() {

}
void endPaint() { }
void clearDevice(void) { }
int getWidth() { }
int getHeight() { }

// Pen
void setPenColor(ACL_Color color) { }
void setPenWidth(int width) { }
void setPenStyle(ACL_Pen_Style style) { }

// Brush
void setBrushColor(ACL_Color color) { }
void setBrushStyle(ACL_Brush_Style style) { }

// Text
void setTextColor(ACL_Color color) { }
void setTextBkColor(ACL_Color color) { }
void setTextSize(int size) { }
void setTextFont(const char *pFontName) { }

void paintText(int x, int y, const char *pStr) { }

void setCaretSize(int w, int h) { }
void setCaretPos(int x, int y) { }
void showCaret() { }
void hideCaret() { }

// Pixel
void putPixel(int x, int y, ACL_Color color) { }
ACL_Color getPixel(int x, int y) { }

// the Point
int getX(void) { }
int getY(void) { }
void moveTo(int x, int y) { }
void moveRel(int dx, int dy) { }

// Lines and Curves
void arc(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXStartArc, int nYStartArc, int nXEndArc, int nYEndArc) { }
void line(int x0, int y0, int x1, int y1) { }
void lineTo(int nXEnd, int nYEnd) { }
void lineRel(int dx, int dy) { }
void polyBezier(const POINT *lppt, int cPoints) { }
void polyLine(const POINT *lppt, int cPoints) { }

// Filled Shapes
void chrod(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2) { }
void ellipse(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect) { }
void pie(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2) { }
void polygon(const POINT *lpPoints, int nCount) { }
void rectangle(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect) { }
void roundrect(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, \
    int nWidth, int nHeight) { }

// Image
void loadImage(const char *pImageFileName, ACL_Image *pImage) { }
void freeImage(ACL_Image *pImage) { }

void putImage(ACL_Image *pImage, int x, int y) { }
void putImageScale(ACL_Image *pImage, int x, int y, int width, int height) { }
void putImageTransparent(ACL_Image *pImage, int x, int y, int width, int height, ACL_Color bkColor) { }


void initConsole(void) { }
