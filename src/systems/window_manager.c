#include "systems/window_manager.h"
#include "data/globals.h"

#include "raylib.h"

void WindowManager_Init() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Falloff");
}

bool WindowManager_WindowShouldClose() {
    return WindowShouldClose();
}