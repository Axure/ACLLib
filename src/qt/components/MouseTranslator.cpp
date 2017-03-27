//
// Created by lluvi on 2016/9/7.
//

#include "functionalities/events.h"
#include <Qt>

#include "MouseTranslator.h"
int buttonFromQt(int qtButtonCode) {
  switch (qtButtonCode) {
    case Qt::LeftButton:
      return LEFT_BUTTON;
    case Qt::RightButton:
      return RIGHT_BUTTON;
    case Qt::MiddleButton:
      return MIDDLE_BUTTON;
    default:
      return NO_BUTTON;
  }
}
