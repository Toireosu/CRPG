#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H 

#include "data/scene.h"

/**
 * @brief Update function for every entity in given scene.
 * 
 * @param scene The scene context to update entities in.
 */
void EntityManager_Tick(Scene* scene);

#endif 