#include "acllib.h"
#include <stdio.h>

int firstY = 120;
int secondY = 220;

void timerCallback(int timerId) {
  beginPaint();
  if (timerId > 100) {
    line(10, 10, timerId, firstY);
    firstY += 10;
  } else {
    line(10, 10, timerId, secondY);
    secondY += 20;
  }
  endPaint();
}

ACL_Image img;
int Setup() {
  initWindow("Test", DEFAULT, DEFAULT, 800, 600);
  msgBox("This", "That", 0);
  initConsole();
  printf("Hello\n");

  loadImage("lena.jpg",&img);
  beginPaint();

  putImage(&img,0,0);
  line(10, 10, 100, 100);
  showCaret();
  endPaint();
  beginPaint();

  line(10, 100, 100, 10);

  registerTimerEvent(timerCallback);
  startTimer(100, 1000);
  startTimer(200, 500);

  endPaint();
  return 0;
}
