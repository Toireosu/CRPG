#ifndef ENGINE_H
#define ENGINE_H

#include "data/scene.h"

/**
 * @brief Initializes the engine and all subcomponents.
 */
void Engine_Init();

/**
 * @brief Loads given scene by id.
 * 
 * @param id The id of the scene to be loaded.
 */
void Engine_LoadScene(int id);

/**
 * @brief Runs the logic for the game.
 */
void Engine_Run();

/**
 * @brief Gets current running scene.
 */
Scene* Engine_GetScene();

#endif 