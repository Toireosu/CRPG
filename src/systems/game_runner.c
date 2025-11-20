#include "systems/game_runner.h"

#include "systems/renderer.h"
#include "systems/mouse_manager.h"

void GameRunner_Run(Game* game) {
    MouseManager_TakeInput(game);
    Renderer_RenderGame(game);
}