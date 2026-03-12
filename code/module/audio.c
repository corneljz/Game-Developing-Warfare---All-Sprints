/*
This module stores the implementation of the functions contained in the
audio.h header file.
*/

#include "settings.h"
#include "audio.h"

audio audio_init(){
    audio new_audio = {0};
    InitAudioDevice();
    SetMasterVolume(game_volume);
    new_audio.bg_music = LoadMusicStream("../assets/audios/bg_music.ogg");
    PlayMusicStream(new_audio.bg_music);

    return new_audio;
}

void audio_update(audio* audio){
    UpdateMusicStream(audio->bg_music);
}

void audio_close(audio* audio){
    UnloadMusicStream(audio->bg_music);
    CloseAudioDevice();
}