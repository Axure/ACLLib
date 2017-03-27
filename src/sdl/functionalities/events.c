//
// Created by zhenghu on 16-9-10.
//
#include <stdlib.h>
#include "functionalities/events.h"
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_events.h>

extern TimerEventCallback timerEventCallback;

typedef struct int_pair_s {
  int key, value;
} int_pair_t;

typedef struct linear_table_s {
  int size;
  int *storage;
} linear_table_t;

void linear_table_init(linear_table_t *linear_table, int size) {
  linear_table->size = size;
  linear_table->storage = malloc(sizeof(int) * size);
};

Uint32 _timer_handler (Uint32 interval, void *param) {
  SDL_Event event;
  SDL_UserEvent userevent;

  /* In this example, our callback pushes a function
  into the queue, and causes our callback to be called again at the
  same interval: */

  userevent.type = SDL_USEREVENT;
  userevent.code = 0;
  userevent.data1 = timerEventCallback;
  userevent.data2 = param;

  event.type = SDL_USEREVENT;
  event.user = userevent;

  SDL_PushEvent(&event);
  return(interval);

}

void registerKeyboardEvent(KeyboardEventCallback callback) {

}
void registerCharEvent(CharEventCallback callback) {

}
void registerMouseEvent(MouseEventCallback callback) {}
void registerTimerEvent(TimerEventCallback callback) {
  timerEventCallback = callback;
}
int timerId;
void startTimer(int timerID, int timeinterval) {
  timerId = timerID;
  int sdl_timer_id = SDL_AddTimer(timeinterval, _timer_handler, &timerId);
}
void cancelTimer(int timerID) {

}
