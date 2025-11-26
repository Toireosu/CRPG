#define PLATFORM_DESKTOP_GLFW

#include "data/game.h"
#include "data/scene.h"
#include "systems/game_runner.h"
#include "systems/window_handler.h"
#include "systems/character_controller.h"
#include <stdlib.h>
#include "systems/renderer.h"
#include "systems/path_finding.h"


int main(int argc, char** argv) {
    WindowHandler_Init();

    Game* game = (Game*)malloc(sizeof(Game));

    Game_Init(game);
    Renderer_Init();
    EventLog_Init();


    game->scene = (Scene*)malloc(sizeof(Scene));
    Scene_Init(game->scene); 

    // Mock add entities

    Entity entity;
    Entity_Init(&entity, ET_CHARACTER, (Vector2){ 0, 2 });

    Scene_Add(game->scene, entity);

    CharacterController_SetCharacter(&game->scene->entities[0]);

    Entity_Init(&entity, ET_CHARACTER, (Vector2){ 1, 5 });
    Scene_Add(game->scene, entity);

    // Mock setup map

    for (int y = 0; y < game->scene->map.height; y++) {
        for (int x = 0; x < game->scene->map.width; x++) {
            Map_SetBackground(&game->scene->map, x, y, 1);
        }   
    }

    Map_SetMidground(&game->scene->map, 0, 9, 0, 2);
    Map_SetMidground(&game->scene->map, 0, 8, 0, 2);    
    Map_SetMidground(&game->scene->map, 0, 7, 0, 2);    

    Map_SetMidground(&game->scene->map, 0, 9, 3, 3);
    Map_SetMidground(&game->scene->map, 1, 9, 3, 3);
    Map_SetMidground(&game->scene->map, 2, 9, 3, 3);

    Map_SetMidground(&game->scene->map, 2, 9, 1, 2);
    Map_SetMidground(&game->scene->map, 2, 8, 1, 2);    
    Map_SetMidground(&game->scene->map, 2, 7, 1, 2); 

    Map_SetMidground(&game->scene->map, 2, 7, 2, 3);
    Map_SetMidground(&game->scene->map, 0, 7, 2, 3);    

    PathFinding_Build(game->scene);

    while (!WindowHandler_WindowShouldClose()) {
        GameRunner_Run(game);
    }
}