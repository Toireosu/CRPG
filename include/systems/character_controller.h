#ifndef CHARACTER_CONTROLLER_H 
#define CHARACTER_CONTROLLER_H

#include "data/entity.h"
#include "data/game.h"

Entity* CharacterController_GetCharacter();
void CharacterController_SetCharacter(Entity* entity);
bool CharacterController_TakeInput(Game* game);

#endif