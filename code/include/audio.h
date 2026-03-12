/*
This file contains function prototypes for the audio module.
*/

#ifndef AUDIO_H
#define AUDIO_H

#include "raylib.h"

typedef struct audio{
    Music bg_music;
} audio;

audio audio_init();
void audio_update(audio* audio);
void audio_close(audio* audio);

#endif
