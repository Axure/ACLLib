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

typedef struct acl_timer_s {
  int timer_id;
} acl_timer_t;

TimerEventCallback timerEventCallback = NULL;

gboolean acl_timer_callback(gpointer data) {
  if (timerEventCallback != NULL) {
    printf("Calling the callback");
    timerEventCallback(G_GET(data, acl_timer_t, timer_id));
  }
  return TRUE;
}

typedef struct acl_ellipse_s {
  int left_rect;
  int top_rect;
  int right_rect;
  int bottom_rect;
} acl_ellipse_t;

GtkWidget *window;
GArray *acl_ellipses;
GArray *acl_timers;

/**
 * The event loop.
 * @param widget
 * @param cr
 * @param data
 * @return
 */
gboolean
draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data) {
  guint width, height;
  GdkRGBA color;
  GtkStyleContext *context;

  double current_x = 0, current_y = 0;

  context = gtk_widget_get_style_context(widget);

  width = gtk_widget_get_allocated_width(widget);
  height = gtk_widget_get_allocated_height(widget);

  gtk_render_background(context, cr, 0, 0, width, height);
  cairo_set_line_width(cr, 1);
//  cairo_arc(cr,
//            width / 2.0, height / 2.0,
//            MIN (width, height) / 2.0,
//            0, 2 * G_PI);
//  cairo_close_path(cr);
//
//  gtk_style_context_get_color(context,
//                              gtk_style_context_get_state(context),
//                              &color);
//  cairo_set_source_rgba(cr, 0.8, 0.0, 0.0, 0.7);
//
//  cairo_fill_preserve(cr);
//
//  cairo_restore(cr);
//  cairo_stroke(cr);

  for (int i = 0; i < acl_ellipses->len; ++i) {
    printf("Painted ellipse");
    cairo_set_line_width(cr, 2);
    acl_ellipse_t *current_ellipse = &g_array_index(acl_ellipses, acl_ellipse_t, i);
    double x = (current_ellipse->left_rect + current_ellipse->right_rect) / 2.0;
    double y = (current_ellipse->top_rect + current_ellipse->bottom_rect) / 2.0;
    double radius_x = (current_ellipse->right_rect - current_ellipse->left_rect) / 2.0;
    double radius_y = (current_ellipse->bottom_rect - current_ellipse->top_rect) / 2.0;
    cairo_translate(cr, x - current_x, y - current_y);
    current_x = x;
    current_y = y;
    cairo_scale(cr, 1, radius_y / radius_x);
    cairo_arc(cr, 0, 0, radius_x, 0, 2 * G_PI);
    cairo_close_path(cr);
    cairo_stroke(cr);
    cairo_scale(cr, 1, 1); // TODO: Is this needed?
  }

//  cairo_fill (cr);

  return FALSE;
}

/**
 * Initialize the window.
 * @param app
 * @param user_data
 */
static void
activate(GtkApplication *app,
         gpointer user_data) {

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (window), G_GET(user_data, window_info_s, title));
  gtk_window_set_default_size(
      GTK_WINDOW (window),
      G_GET(user_data, window_info_s, width),
      G_GET(user_data, window_info_s, height)
  );
  gtk_window_set_resizable(window, FALSE);
  gtk_window_move(
      GTK_WINDOW(window),
      G_GET(user_data, window_info_s, left),
      G_GET(user_data, window_info_s, top)
  );

  GtkWidget *drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area, G_GET(user_data, window_info_s, width), G_GET(user_data, window_info_s, height));
  g_signal_connect (G_OBJECT(drawing_area), "draw",
                    G_CALLBACK(draw_callback), NULL);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
  gtk_container_add(GTK_CONTAINER(window), box);


//  GtkWidget *button = gtk_button_new();

  gtk_container_add(GTK_CONTAINER(box), drawing_area);
//  gtk_container_add(GTK_CONTAINER(box), button);
  gtk_widget_show_all(window);
}

/**
 * The main function.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc,
         char **argv) {
  init_datastructure();
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

void init_datastructure() {
  printf("Initializing data structures.\n");
  acl_ellipses = g_array_new(FALSE, FALSE, sizeof(acl_ellipse_t));
  acl_timers = g_array_new(FALSE, FALSE, sizeof(acl_timer_t));
  printf("Initialized data structures.\n");

}

void initWindow(const char title[], int left, int top, int width, int height) {
  window_info.title = (char *) title;
  window_info.left = left;
  window_info.top = top;
  window_info.height = height;
  window_info.width = width;


//  GtkApplication *app;
//  app = gtk_application_window_new(app);

}
void msgBox(const char title[], const char text[], int flag) {
//  gtk_dialog_new();
}

void registerKeyboardEvent(KeyboardEventCallback callback) {

}
void registerCharEvent(CharEventCallback callback) {

}
void registerMouseEvent(MouseEventCallback callback) {}
void registerTimerEvent(TimerEventCallback callback) {
  timerEventCallback = callback;
}

void startTimer(int timerID, int timeinterval) {
  acl_timer_t new_timer = {timerID};
  g_array_append_val(acl_timers, new_timer);
  g_timeout_add(timeinterval, acl_timer_callback, &(g_array_index(acl_timers, acl_timer_t, acl_timers->len - 1))); // TODO: better way to get the element.
  // TODO: currently the timer data is not released.
}
void cancelTimer(int timerID) {}

// Sound
void loadSound(const char *fileName, ACL_Sound *pSound) {}
void playSound(ACL_Sound soundID, int repeat) {}
void stopSound(ACL_Sound soundID) {}

// Paint
void beginPaint() {

}
void endPaint() {
//gdk_window_invalidate_rect(window, TRUE);
  gtk_widget_queue_draw(window); // TODO: Is this elegant?
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
  printf("Appending ellipse\n");
  acl_ellipse_t new_ellipse = {
      nLeftRect, nTopRect, nRightRect, nBottomRect
  };
  g_array_append_val(acl_ellipses, new_ellipse);
  printf("Appended ellipse\n");
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
