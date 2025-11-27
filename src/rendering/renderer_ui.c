#include "rendering/renderer.h"

#include "data/event_log.h"
#include "systems/window_handler.h"
#include "raylib.h"

void Renderer_RenderUI(Game* game) {
    // Temp
    BeginScissorMode(0, WINDOW_HANDLER_HEIGHT - 150, 400, 150);

    for (int i = 0; i < EVENT_LOG_MAX_COUNT; i++) {
        DrawText(
            EventLog_Get(i), 
            0,
            WINDOW_HANDLER_HEIGHT - (i + 1) * 20,
            20,
            WHITE
        );
    }

    EndScissorMode();
}
