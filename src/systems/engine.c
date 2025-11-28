#include "systems/engine.h"

#include "rendering/renderer.h"
#include "systems/mouse_manager.h"
#include "systems/entity_manager.h"
#include "systems/window_manager.h"
#include "systems/message_log.h"
#include "systems/scene_camera.h"
#include "systems/character_controller.h"
#include "systems/navigation.h"


struct {
    Scene scene;
} engine;

// TODO: Temp remove
static void MakeHouse(Coordinates v) {
    Map_SetMidground(&engine.scene.map, 0 + v.x, 2 + v.y, 0, 2);
    Map_SetMidground(&engine.scene.map, 0 + v.x, 1 + v.y, 0, 2);    
    Map_SetMidground(&engine.scene.map, 0 + v.x, 0 + v.y, 0, 2);    

    Map_SetMidground(&engine.scene.map, 0 + v.x, 2 + v.y, 3, 3);
    Map_SetMidground(&engine.scene.map, 1 + v.x, 2 + v.y, 3, 3);
    Map_SetMidground(&engine.scene.map, 2 + v.x, 2 + v.y, 3, 3);

    Map_SetMidground(&engine.scene.map, 2 + v.x, 2 + v.y, 1, 2);
    Map_SetMidground(&engine.scene.map, 2 + v.x, 1 + v.y, 1, 2);    
    Map_SetMidground(&engine.scene.map, 2 + v.x, 0 + v.y, 1, 2); 

    Map_SetMidground(&engine.scene.map, 2 + v.x, 0 + v.y, 2, 3);
    Map_SetMidground(&engine.scene.map, 0 + v.x, 0 + v.y, 2, 3);   
    
    Map_SetForeground(&engine.scene.map, v.x, v.y, 1);
    Map_SetForeground(&engine.scene.map, v.x + 1, v.y, 1);
    Map_SetForeground(&engine.scene.map, v.x + 2, v.y, 1);
    
    Map_SetForeground(&engine.scene.map, v.x, v.y + 1, 1);
    Map_SetForeground(&engine.scene.map, v.x + 1, v.y + 1, 1);
    Map_SetForeground(&engine.scene.map, v.x + 2, v.y + 1, 1);
    
    Map_SetForeground(&engine.scene.map, v.x, v.y + 2, 1);
    Map_SetForeground(&engine.scene.map, v.x + 1, v.y + 2, 1);
    Map_SetForeground(&engine.scene.map, v.x + 2, v.y + 2, 1);
}

void Engine_Init() {
    WindowManager_Init();
    Renderer_Init();
    MessageLog_Init();
    
    // TODO: Set gamestate
    // engine.scene = NULL;
}

void Engine_LoadScene(int id) {
    Scene_Init(&engine.scene);

    // TODO: REMOVE Mock setup map ------------------------
    for (int y = 0; y < engine.scene.map.height; y++) {
        for (int x = 0; x < engine.scene.map.width; x++) {
            Map_SetBackground(&engine.scene.map, x, y, 1);
        }   
    }
    // ---------------------------------------------------

    MakeHouse((Coordinates){0, 6});

    MakeHouse((Coordinates){6, 4});

    MakeHouse((Coordinates){6, 7});

    Map_SetMidground(&engine.scene.map, 7, 6, 3, 0);

    Navigation_Init(&engine.scene.map);

    // TODO: REMOVE Mock setup entities ------------------------

    Entity* entity0 = Scene_CreateEntity(&engine.scene);
    Entity_Init(entity0, ET_CHARACTER, (Coordinates){ 0, 2 });

    CharacterController_SetCharacter(&engine.scene.entities[0]);

    Entity* entity1 = Scene_CreateEntity(&engine.scene);
    Entity_Init(entity1, ET_CHARACTER, (Coordinates){ 1, 7 });

    // ---------------------------------------------------
    
    // TODO: Change the way we set this..
    Scene_SetPlayer(&engine.scene, entity0);
    
    Renderer_MapInit(&engine.scene.map);

    SceneCamera_Init();
    SceneCamera_SetPosition((Vector2){0, -130});
}

void Engine_Run() {
    float delta = GetFrameTime();

    MouseManager_TakeInput();

    EntityManager_Tick(&engine.scene);

    Renderer_Render();
}

Scene* Engine_GetScene() { return &engine.scene; }