/*
This file contains function prototypes for the scene module.
*/

#ifndef SCENE_H
#define SCENE_H

#include "settings.h"

typedef struct scene{
    Texture2D mainmenu_background;     // The background texture for the main menu.
    Texture2D game_background_1;         // The background texture for the game scene.
} Scene;

Scene scene_init(Settings* game_settings);                     // Initializes the game scene.
void UpdateScene(Scene* scene, Settings* game_settings);
void draw_mainmenu(Scene* scene);        // Draws the main menu background.
#endif