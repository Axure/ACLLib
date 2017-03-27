//
// Created by Colliot on 2016/9/6.
//

#ifndef PROJECT_TIMER_H
#define PROJECT_TIMER_H

#include <QTimer>
#include "../verdigris/src/wobjectdefs.h"

class IntTimer: public QTimer {
  W_OBJECT(IntTimer)
 private:
  int id;
 public:
  IntTimer(QObject *parent, int id);
  void fireTimer();
  W_SLOT(fireTimer)
  int timeoutWithId(int id) W_SIGNAL(timeoutWithId, id)
};

#endif //PROJECT_TIMER_H
