//
// Created by Colliot on 2016/9/6.
//

#ifndef PROJECT_EVENTS_H
#define PROJECT_EVENTS_H

typedef enum {
  NO_BUTTON = 0,
  LEFT_BUTTON,
  MIDDLE_BUTTON,
  RIGHT_BUTTON
} ACL_Mouse_Button;

typedef enum {
  BUTTON_DOWN,
  BUTTON_DOUBLECLICK,
  BUTTON_UP,
  ROLL_UP,
  ROLL_DOWN,
  MOUSEMOVE
} ACL_Mouse_Event;

typedef enum {
  KEY_DOWN,
  KEY_UP
} ACL_Keyboard_Event;

/**
 * Derived from Win32.
 * Using macro definitions directly from another library is not a good practice.
 * Kept only for backward compatibility.
 * If the VK_LEFT macro is defined, there is no need to define the as enum constants.
 * This possibly means "windows.h" is included,
 * which can only happen when compiling the library, on contrary to the examples.
 */
#ifndef VK_LEFT
typedef enum {
  VK_LEFT = 0x25,
  VK_UP = 0x26,
  VK_RIGHT = 0x27,
  VK_DOWN = 0x28,
} ACL_Virtual_Key_Code;
#endif

typedef void (*KeyboardEventCallback)(int key, int event);
typedef void (*CharEventCallback)(char c);
typedef void (*MouseEventCallback)(int x, int y, int button, int event);
typedef void (*TimerEventCallback)(int timerID);


void registerKeyboardEvent(KeyboardEventCallback callback);
void registerCharEvent(CharEventCallback callback);
void registerMouseEvent(MouseEventCallback callback);
void registerTimerEvent(TimerEventCallback callback);


void startTimer(int timerID, int timeinterval);
void cancelTimer(int timerID);



#endif //PROJECT_EVENTS_H
