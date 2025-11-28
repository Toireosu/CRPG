#include "systems/engine.h"

#include "rendering/renderer.h"
#include "systems/mouse_manager.h"
#include "systems/entity_manager.h"

void Engine_Run(Game* game) {
    float delta = GetFrameTime();

    MouseManager_TakeInput(game);

    EntityManager_Tick(game->scene, delta);

    Renderer_Render(game);
}