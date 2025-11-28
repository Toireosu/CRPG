#define PLATFORM_DESKTOP_GLFW

#include "data/game.h"
#include "data/scene.h"
#include "systems/engine.h"
#include "systems/window_manager.h"
#include "systems/character_controller.h"
#include <stdlib.h>
#include "rendering/renderer.h"
#include "systems/navigation.h"
#include "systems/scene_camera.h"
#include "systems/message_log.h"


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
    
    Map_SetForeground(&game->scene->map, v.x, v.y, 1);
    Map_SetForeground(&game->scene->map, v.x + 1, v.y, 1);
    Map_SetForeground(&game->scene->map, v.x + 2, v.y, 1);
    
    Map_SetForeground(&game->scene->map, v.x, v.y + 1, 1);
    Map_SetForeground(&game->scene->map, v.x + 1, v.y + 1, 1);
    Map_SetForeground(&game->scene->map, v.x + 2, v.y + 1, 1);
    
    Map_SetForeground(&game->scene->map, v.x, v.y + 2, 1);
    Map_SetForeground(&game->scene->map, v.x + 1, v.y + 2, 1);
    Map_SetForeground(&game->scene->map, v.x + 2, v.y + 2, 1);
}

int main(int argc, char** argv) {
    WindowManager_Init();

    Game* game = (Game*)malloc(sizeof(Game));

    Game_Init(game);
    Renderer_Init();
    MessageLog_Init();


    game->scene = (Scene*)malloc(sizeof(Scene));
    Scene_Init(game->scene); 

    // Mock setup map

    for (int y = 0; y < game->scene->map.height; y++) {
        for (int x = 0; x < game->scene->map.width; x++) {
            Map_SetBackground(&game->scene->map, x, y, 1);
        }   
    }
    
    MakeHouse(game, (Coordinates){0, 6});

    MakeHouse(game, (Coordinates){6, 4});

    Navigation_Init(&game->scene->map);
    SceneCamera_Init();
    SceneCamera_SetPosition((Vector2){0, -130});

    // Mock add entities

    Entity* entity0 = Scene_CreateEntity(game->scene);
    Entity_Init(entity0, ET_CHARACTER, (Coordinates){ 0, 2 });

    CharacterController_SetCharacter(&game->scene->entities[0]);

    Entity* entity1 = Scene_CreateEntity(game->scene);
    Entity_Init(entity1, ET_CHARACTER, (Coordinates){ 1, 7 });

    Scene_SetPlayer(game->scene, entity0);
    Renderer_MapInit(&game->scene->map);

    while (!WindowManager_WindowShouldClose()) {
        Engine_Run(game);
    }
}