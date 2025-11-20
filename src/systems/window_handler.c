#include "systems/window_handler.h"

#include "raylib.h"

void WindowHandler_Init() {
    InitWindow(WINDOW_HANDLER_WIDTH, WINDOW_HANDLER_HEIGHT, "Falloff");
}

bool WindowHandler_WindowShouldClose() {
    return WindowShouldClose();
}