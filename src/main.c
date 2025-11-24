#define PLATFORM_DESKTOP_GLFW

#include "data/game.h"
#include "data/scene.h"
#include "systems/game_runner.h"
#include "systems/window_handler.h"
#include "systems/character_controller.h"
#include <stdlib.h>
#include "systems/renderer.h"


int main(int argc, char** argv) {
    WindowHandler_Init();

    Game* game = (Game*)malloc(sizeof(Game));

    Game_Init(game);
    Renderer_Init();


    game->scene = (Scene*)malloc(sizeof(Scene));
    Scene_Init(game->scene); 

    Entity entity;
    Entity_Init(&entity, ET_CHARACTER, (Vector2){ 100, 100 });

    Scene_Add(game->scene, entity);

    CharacterController_SetCharacter(&game->scene->entities[0]);

    Entity_Init(&entity, ET_CHARACTER, (Vector2){ 200, 100 });
    Scene_Add(game->scene, entity);

    while (!WindowHandler_WindowShouldClose()) {
        GameRunner_Run(game);
    }
}