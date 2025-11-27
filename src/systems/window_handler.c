#include "systems/window_handler.h"
#include "data/globs.h"

#include "raylib.h"

void WindowHandler_Init() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Falloff");
}

bool WindowHandler_WindowShouldClose() {
    return WindowShouldClose();
}