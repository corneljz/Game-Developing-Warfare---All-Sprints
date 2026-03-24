#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "raylib.h"
#include "pl_mpeg.h"

// Reusable structure for any video cutscene in the game
typedef struct {
    plm_t *mpeg;               // The pl_mpeg decoder instance
    Texture2D frameTexture;    // The GPU texture where video frames are uploaded
    AudioStream audioStream;   // The Raylib audio stream for video sound
    unsigned char *rgbBuffer;  // CPU memory to hold decoded frame data before GPU upload
    bool isPlaying;            // Is the video currently running?
    bool hasEnded;             // Did the video reach the end?
} VideoCutscene;

// Function signatures - consistent with your Init/Run/Draw/End style
void InitCutscene(VideoCutscene *cutscene, const char *fileName);
void UpdateCutscene(VideoCutscene *cutscene);
void UnloadCutscene(VideoCutscene *cutscene);

#endif