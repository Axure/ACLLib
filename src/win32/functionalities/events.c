#include "functionalities/events.h"
#include "window.h"
#include <windows.h>


KeyboardEventCallback g_keyboard = NULL;
MouseEventCallback g_mouse = NULL;
TimerEventCallback g_timer = NULL;
CharEventCallback g_char = NULL;

void registerKeyboardEvent(KeyboardEventCallback callback) {
  g_keyboard = callback;
}

void registerCharEvent(CharEventCallback callback) {
  g_char = callback;
}

void registerMouseEvent(MouseEventCallback callback) {
  g_mouse = callback;
}

void registerTimerEvent(TimerEventCallback callback) {
  g_timer = callback;
}

void startTimer(int id, int timeinterval) {
  SetTimer(g_hWnd, id, timeinterval, NULL);
}

void cancelTimer(int id) {
  KillTimer(g_hWnd, id);
}