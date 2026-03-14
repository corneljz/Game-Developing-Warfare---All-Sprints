/*
This is for scene managing, such as loading and drawing the background.
*/
#include "scene.h"

Scene scene_init(Settings* game_settings){
    /* Initialize the game scene. */
    Scene new_scene = {0};

    //load main menu background
    Image img = LoadImage("../assets/images/background/Mountain/parallax-mountain-bg.png");
    ImageResize(&img, game_settings->window_width, game_settings->window_height);
    new_scene.mainmenu_background = LoadTextureFromImage(img);
    UnloadImage(img);

    //load game background 1
    img = LoadImage("../assets/images/background/Mountain/parallax-mountain-bg.png");
    ImageResize(&img, game_settings->window_width, game_settings->window_height);
    new_scene.game_background_1 = LoadTextureFromImage(img);
    UnloadImage(img);

    return new_scene;
}

// Draws the main menu background.
void draw_mainmenu(Scene* scene) {
    DrawTexture(scene->mainmenu_background, 0, 0, WHITE);
}

// Updates the scene (e.g., animate backgrounds if needed).
void UpdateScene(Scene* scene, Settings* game_settings) {
    // TODO: Implement scene updates, e.g., parallax scrolling or animations.
    // For now, this is a stub.
}