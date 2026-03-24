#define PL_MPEG_IMPLEMENTATION
#include "cutscene.h"
#include <stdlib.h>

// --- Callbacks for the decoder ---

// This function is called by pl_mpeg whenever a new audio frame is ready
void OnAudioCallback(plm_t *mpeg, plm_samples_t *samples, void *user) {
    VideoCutscene *cutscene = (VideoCutscene *)user;

    // We check if the pointer is valid AND if the stream is currently playing.
    // This prevents trying to push audio data into a stream that isn't ready.
    if (cutscene == NULL) return;
    if (IsAudioStreamPlaying(cutscene->audioStream)) {
        UpdateAudioStream(cutscene->audioStream, samples->interleaved, samples->count);
    }
}

// This function is called by pl_mpeg whenever a new video frame is ready
void OnVideoCallback(plm_t *mpeg, plm_frame_t *frame, void *user) {
    VideoCutscene *cutscene = (VideoCutscene *)user;
    
    // 1. Double check the buffer and texture exist
    if (cutscene == NULL || cutscene->rgbBuffer == NULL) {
        printf("DEBUG: Callback failed - Cutscene or Buffer is NULL!\n");
        return;
    }
    
    plm_frame_to_rgba(frame, cutscene->rgbBuffer, frame->width * 4);
    if (cutscene->frameTexture.id > 0) {
        UpdateTexture(cutscene->frameTexture, cutscene->rgbBuffer);
    }
}

// --- Main Functions ---

void InitCutscene(VideoCutscene *cutscene, const char *fileName) {
    cutscene->mpeg = plm_create_with_filename(fileName);
    if (!cutscene->mpeg) {
        printf("FAILED TO LOAD VIDEO: %s\n", fileName);
        return;
    }

    int w = plm_get_width(cutscene->mpeg);
    int h = plm_get_height(cutscene->mpeg);

    if (cutscene->rgbBuffer) free(cutscene->rgbBuffer);
    cutscene->rgbBuffer = (unsigned char *)malloc(w * h * 4);

    for (int i = 0; i < w * h * 4; i += 4) {
        cutscene->rgbBuffer[i] = 0; cutscene->rgbBuffer[i+1] = 255; 
        cutscene->rgbBuffer[i+2] = 0; cutscene->rgbBuffer[i+3] = 255;
    }

    Image tempImg = GenImageColor(w, h, BLACK);
    if (cutscene->frameTexture.id > 0) UnloadTexture(cutscene->frameTexture);
    cutscene->frameTexture = LoadTextureFromImage(tempImg);
    UnloadImage(tempImg);

    int samplerate = plm_get_samplerate(cutscene->mpeg);
    if (samplerate <= 0) samplerate = 44100;
    cutscene->audioStream = LoadAudioStream(samplerate, 16, 2);
    SetAudioStreamVolume(cutscene->audioStream, 1.0f);
    PlayAudioStream(cutscene->audioStream);

    plm_set_video_decode_callback(cutscene->mpeg, OnVideoCallback, cutscene);
    plm_set_audio_decode_callback(cutscene->mpeg, OnAudioCallback, cutscene);
}

void UnloadCutscene(VideoCutscene *cutscene) {
    if (cutscene->mpeg) plm_destroy(cutscene->mpeg);
    UnloadTexture(cutscene->frameTexture);
    UnloadAudioStream(cutscene->audioStream);
    if (cutscene->rgbBuffer) free(cutscene->rgbBuffer);
}