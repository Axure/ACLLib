//
// Created by lluvi on 2016/9/7.
//

#ifndef ACLLIB_KEYBOARDTRANSLATOR_H
#define ACLLIB_KEYBOARDTRANSLATOR_H
#include <Qt>
#include "functionalities/events.h"

class KeyboardTranslator {
 public:
  int fromQtKeyCode(int qtKeyCode) {
    switch (qtKeyCode) {
      case Qt::Key_Up:
        return VK_UP;
      case Qt::Key_Down:
        return VK_DOWN;
      case Qt::Key_Left:
        return VK_LEFT;
      case Qt::Key_Right:
        return VK_RIGHT;
      default:
        return -1;
    }
  }
};


#endif //ACLLIB_KEYBOARDTRANSLATOR_H
