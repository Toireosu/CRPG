#include "systems/game_runner.h"

#include "systems/renderer.h"
#include "systems/mouse_manager.h"
#include "systems/entity_controller.h"

void GameRunner_Run(Game* game) {
    float delta = GetFrameTime();

    MouseManager_TakeInput(game);

    EntityController_Tick(game->scene, delta);

    Renderer_RenderGame(game);
}