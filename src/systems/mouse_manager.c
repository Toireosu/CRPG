#include "systems/mouse_manager.h"

#include <stddef.h>

#include "systems/character_controller.h"
#include "systems/scene_camera.h"
#include "systems/window_manager.h"

#include "data/globals.h"
#include "systems/message_log.h"

#include "raymath.h"
#include "data/scene.h"
#include "systems/engine.h"

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

static bool MouseManager_HandleEntities() {
    // if (!game->scene) return false;

    const Scene* scene = Engine_GetScene();

    for (int i = 0; i < scene->entities_count; i++) {
        const Entity* entity =  &scene->entities[i];
        Rectangle rect = (Rectangle) { entity->position.x - 0.25, entity->position.y - 2, 0.5, 2 };

        if (CheckCollisionPointRec(SceneCamera_ScreenToMap(GetMousePosition()), rect)) {

            if (MouseManager.last_hovered != entity)
                MessageLog_Push("You see: An entity.");
            return MouseManager_Hover((void*)entity);
        }
    }
} 

#define SCROLL_FIELD_SIZE 50
#define SCROLL_SPEED 40

static bool MouseManager_ScrollScreen() {
    // TODO: Check if we are in scene gamestate
    // if (!game->scene) return false;

    float delta = GetFrameTime();

    Vector2 mouse_position = GetMousePosition();
    if (mouse_position.x < SCROLL_FIELD_SIZE) SceneCamera_Move(Vector2Scale((Vector2){ -1, 0 },  SCROLL_SPEED));
    if (mouse_position.y < SCROLL_FIELD_SIZE) SceneCamera_Move(Vector2Scale((Vector2){ 0, -1 },  SCROLL_SPEED));
    if (mouse_position.x > WINDOW_WIDTH - SCROLL_FIELD_SIZE) SceneCamera_Move(Vector2Scale((Vector2){ 1, 0 },  SCROLL_SPEED));
    if (mouse_position.y > WINDOW_HEIGHT - SCROLL_FIELD_SIZE) SceneCamera_Move(Vector2Scale((Vector2){ 0, 1 },  SCROLL_SPEED));
}

void MouseManager_TakeInput() {
    // Loop over all entities to check for input

    if (CharacterController_TakeInput())
        return;

    if (MouseManager_ScrollScreen())
        return;

    if (MouseManager_HandleEntities())
        return;
}