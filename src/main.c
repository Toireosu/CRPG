#define PLATFORM_DESKTOP_GLFW

#include "data/scene.h"
#include "systems/engine.h"
#include "systems/window_manager.h"
#include "systems/character_controller.h"
#include <stdlib.h>
#include "rendering/renderer.h"
#include "systems/navigation.h"
#include "systems/scene_camera.h"
#include "systems/message_log.h"

int main(int argc, char** argv) {
    Engine_Init();

    // Mock add entities
    Engine_LoadScene(0);

    while (!WindowManager_WindowShouldClose()) {
        Engine_Run();
    }
}