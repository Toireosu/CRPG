#include "systems/mouse_manager.h"

#include <stddef.h>

#include "systems/character_controller.h"
#include "systems/world_camera.h"

struct {
    void* last_hovered;
} MouseManager;

void MouseManager_Init() {
    MouseManager.last_hovered = NULL;
}

static bool MouseManager_Hover(void* hovered) {
    MouseManager.last_hovered = hovered;
    return true;
}

static bool MouseManager_HandleEntities(Game* game) {
    if (!game->scene) return false;

    const Scene* scene = game->scene;

    for (int i = 0; i < scene->entities_count; i++) {
        const Entity* entity =  &scene->entities[i];
        Rectangle rect = (Rectangle) { entity->position.x, entity->position.y, 1, 1 };

        if (CheckCollisionPointRec(WorldCamera_ScreenToMap(GetMousePosition()), rect)) {

            if (MouseManager.last_hovered != entity)
                EventLog_Push("You see: An entity.");
            return MouseManager_Hover((void*)entity);
        }
    }
} 

void MouseManager_TakeInput(Game* game) {
    // Loop over all entities to check for input

    if (CharacterController_TakeInput(game))
        return;

    if (MouseManager_HandleEntities(game))
        return;
}