//
// Created by Colliot on 2016/9/6.
//

#ifndef PROJECT_AUDIO_H
#define PROJECT_AUDIO_H

typedef int ACL_Sound;
// Sound
void loadSound(const char *fileName, ACL_Sound *pSound);
void playSound(ACL_Sound soundID, int repeat);
void stopSound(ACL_Sound soundID);

#endif //PROJECT_AUDIO_H
