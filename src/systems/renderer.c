#include "systems/renderer.h"
#include "data/event_log.h"
#include "systems/window_handler.h"

#include "raylib.h"

static void Renderer_RenderEntity(const Entity* entity) {
    DrawRectangle(
        entity->position.x,
        entity->position.y,
        16,
        16,
        RED
    );
}

static void Renderer_RenderScene(Scene* scene) {
    if (!scene) return;

    for (int i = 0; i < scene->entities_count; i++) {
        Entity* entity = &scene->entities[i];
         
        Renderer_RenderEntity(entity);
    }
}

static void Renderer_RenderUI(Game* game) {
    // Temp
    for (int i = 0; i < EVENT_LOG_MAX_COUNT; i++) {
        DrawText(
            EventLog_Get(&game->event_log, i), 
            0,
            WINDOW_HANDLER_HEIGHT - i * 20,
            20,
            WHITE
        );
    }
}

void Renderer_RenderGame(Game* game) {

    BeginDrawing();

    ClearBackground(BLACK);

    Renderer_RenderScene(game->scene);

    Renderer_RenderUI(game);

    EndDrawing();
}