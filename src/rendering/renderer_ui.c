#include "rendering/renderer.h"

#include "systems/message_log.h"
#include "systems/window_manager.h"
#include "data/globals.h"
#include "raylib.h"

void Renderer_RenderUI() {
    // Temp
    BeginScissorMode(0, WINDOW_HEIGHT - 150, 400, 150);

    for (int i = 0; i < MESSAGE_LOG_MAX_COUNT; i++) {
        DrawText(
            MessageLog_Get(i), 
            0,
            WINDOW_HEIGHT - (i + 1) * 20,
            20,
            WHITE
        );
    }

    EndScissorMode();
}
