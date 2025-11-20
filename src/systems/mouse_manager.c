#include "systems/mouse_manager.h"

#include <stddef.h>

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
        Rectangle rect = (Rectangle) { entity->position.x, entity->position.y, entity->size.x, entity->size.y };

        if (CheckCollisionPointRec(GetMousePosition(), rect)) {

            if (MouseManager.last_hovered != entity)
                EventLog_Push(&game->event_log, "You see: An entity.");
            return MouseManager_Hover((void*)entity);
        }
    }
} 

void MouseManager_TakeInput(Game* game) {
    // Loop over all entities to check for input

    if (MouseManager_HandleEntities(game))
        return;
}