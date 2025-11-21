#include "systems/character_controller.h"
#include "raylib.h"

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
        Entity_Move(CharacterController.entity, mouse_position);
        return true;
    }

    return false;
}