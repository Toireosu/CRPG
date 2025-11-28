#include "systems/character_controller.h"
#include "raylib.h"
#include "systems/scene_camera.h"
#include "raymath.h"

struct {
    Entity* entity;
} CharacterController;

Entity* CharacterController_GetCharacter() {
    return CharacterController.entity;
}

void CharacterController_SetCharacter(Entity* entity) {
    CharacterController.entity = entity;
}

bool CharacterController_TakeInput(Game* game)  {
    // Temp
    Vector2 mouse_position = GetMousePosition();
    
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 map_pos = SceneCamera_ScreenToMap(mouse_position);
        map_pos.x = round(map_pos.x);
        map_pos.y = round(map_pos.y);

        Entity_BeginMove(CharacterController.entity, Coordinates_FromVector2(SceneCamera_ScreenToMap(mouse_position)));
        return true;
    }

    return false;
}