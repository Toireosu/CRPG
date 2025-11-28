#ifndef CHARACTER_CONTROLLER_H 
#define CHARACTER_CONTROLLER_H

#include "data/entity.h"

/**
 * @brief Gets current controlled character.
 * 
 * @return The controlled character.
 */
Entity* CharacterController_GetCharacter();

/**
 * @brief Sets current controlled character.
 * 
 * @param entity The new character to be controlled.
 */
void CharacterController_SetCharacter(Entity* entity);

/**
 * @brief Handles input for the current controlled character.
 * 
 * @return True if the function handled the input, false if the input should be passed along to next manager.
 */
bool CharacterController_TakeInput();

#endif