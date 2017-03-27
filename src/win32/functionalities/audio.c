#include "functionalities/audio.h"
#include <windows.h>
#include <string.h>
#include <stdio.h>

int g_soundID = 0;

void loadSound(const char *fileName, ACL_Sound *pSound) {
  char *cmdStr;
  int len = strlen(fileName) * sizeof(char);
  len += 64;
  cmdStr = (char *) malloc(len);
  sprintf(cmdStr, "open \"%s\" type mpegvideo alias S%d", fileName, g_soundID);
  *pSound = g_soundID;
  ++g_soundID;
  mciSendStringA(cmdStr, NULL, 0, NULL);
  free(cmdStr);
}

void playSound(int sid, int repeat) {
  char cmdStr[32];
  stopSound(sid);
  if (repeat)
    sprintf(cmdStr, "play S%d from 0 repeat", sid);
  else
    sprintf(cmdStr, "play S%d from 0", sid);
  mciSendStringA(cmdStr, NULL, 0, NULL);
}

void stopSound(int sid) {
  char cmdStr[32];
  sprintf(cmdStr, "stop S%d", sid);
  mciSendStringA(cmdStr, NULL, 0, NULL);
}
