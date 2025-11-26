#define PLATFORM_DESKTOP_GLFW

#include "data/game.h"
#include "data/scene.h"
#include "systems/game_runner.h"
#include "systems/window_handler.h"
#include "systems/character_controller.h"
#include <stdlib.h>
#include "systems/renderer.h"
#include "systems/path_finding.h"
#include "systems/world_camera.h"


void MakeHouse(Game* game, Coordinates v) {
    Map_SetMidground(&game->scene->map, 0 + v.x, 2 + v.y, 0, 2);
    Map_SetMidground(&game->scene->map, 0 + v.x, 1 + v.y, 0, 2);    
    Map_SetMidground(&game->scene->map, 0 + v.x, 0 + v.y, 0, 2);    

    Map_SetMidground(&game->scene->map, 0 + v.x, 2 + v.y, 3, 3);
    Map_SetMidground(&game->scene->map, 1 + v.x, 2 + v.y, 3, 3);
    Map_SetMidground(&game->scene->map, 2 + v.x, 2 + v.y, 3, 3);

    Map_SetMidground(&game->scene->map, 2 + v.x, 2 + v.y, 1, 2);
    Map_SetMidground(&game->scene->map, 2 + v.x, 1 + v.y, 1, 2);    
    Map_SetMidground(&game->scene->map, 2 + v.x, 0 + v.y, 1, 2); 

    Map_SetMidground(&game->scene->map, 2 + v.x, 0 + v.y, 2, 3);
    Map_SetMidground(&game->scene->map, 0 + v.x, 0 + v.y, 2, 3);    
}

int main(int argc, char** argv) {
    WindowHandler_Init();

    Game* game = (Game*)malloc(sizeof(Game));

    Game_Init(game);
    Renderer_Init();
    EventLog_Init();


    game->scene = (Scene*)malloc(sizeof(Scene));
    Scene_Init(game->scene); 

    WorldCamera_Init();
    WorldCamera_SetPosition((Vector2){0, -130});

    // Mock add entities

    Entity entity;
    Entity_Init(&entity, ET_CHARACTER, (Coordinates){ 0, 2 });

    Scene_Add(game->scene, entity);

    CharacterController_SetCharacter(&game->scene->entities[0]);

    Entity_Init(&entity, ET_CHARACTER, (Coordinates){ 1, 5 });
    Scene_Add(game->scene, entity);

    // Mock setup map

    MakeHouse(game, (Coordinates){0, 6});

    MakeHouse(game, (Coordinates){6, 4});

    for (int y = 0; y < game->scene->map.height; y++) {
        for (int x = 0; x < game->scene->map.width; x++) {
            Map_SetBackground(&game->scene->map, x, y, 1);
        }   
    }

    PathFinding_Build(game->scene);

    while (!WindowHandler_WindowShouldClose()) {
        GameRunner_Run(game);
    }
}