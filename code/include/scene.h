/*
This file contains function prototypes for the scene module.
*/

#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"

typedef struct scene{
    Texture2D mainmenu_background;     // The background texture for the main menu.
    Texture2D game_background_1;         // The background texture for the game scene.
} scene;

scene scene_init();                     // Initializes the game scene.
void draw_mainmenu(scene* scene);        // Draws the main menu background.
#endif