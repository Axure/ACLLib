//
// Created by Colliot on 2016/9/6.
//

#include "IntTimer.h"
#include "../verdigris/src/wobjectimpl.h"

W_OBJECT_IMPL(IntTimer)
void IntTimer::fireTimer() {
  emit timeoutWithId(id);
}

IntTimer::IntTimer(QObject *parent, int id) : QTimer(parent), id(id) {
  connect(this, SIGNAL(timeout()), this, SLOT(fireTimer()));
}
