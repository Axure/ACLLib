#include "acllib.h"
#include <stdio.h>

int Setup() {
  initWindow("Test", DEFAULT, DEFAULT, 800, 600);
  msgBox("This", "That", 0);
  initConsole();
  printf("Hello\n");

  beginPaint();

  line(10, 10, 100, 100);
  ellipse(0, 0, 400, 200);

  endPaint();

  return 0;
}
