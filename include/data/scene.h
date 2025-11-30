#ifndef SCENE_H
#define SCENE_H

#define SCENE_MAX_ENTITY_COUNT 100

#include "kvec.h"
#include "entity.h"
#include "map.h"
/**
 * @struct Scene
 * @brief A struct containing the data used by an in-game "level" i.e. map-layout and entities.
 */
typedef struct Scene {
    Entity entities[SCENE_MAX_ENTITY_COUNT];
    int entities_count;
    Entity* player;
    Map map;
} Scene;

/**
 * @brief Initializes a given scene.
 * 
 * @param scene The Scene to be initialized.
 */
void Scene_Init(Scene* scene);

/**
 * @brief Creates an entity, adds it to a scenes entity vector, and returns a reference to it.
 * 
 * @param scene The Scene which the entity will be created in.
 * @return A reference to the newly created entity. 
 */
Entity* Scene_CreateEntity(Scene* scene);

/**
 * @brief Sets the player entity for a given scene.
 * 
 * @param scene The Scene in which to set the player.
 * @param entity The player Entity.
 * @note The player must also be added using CreateEntity for the scene logic to work.
 */
void Scene_SetPlayer(Scene* scene, Entity* entity);

typedef kvec_t(Entity*) EntityVector;

// Must call kv_destroy after use
/**
 * @brief Gets all entities in given circle of scene (map space).
 * 
 * @param scene The scene context.
 * @param center The center of the circle.
 * @param radius The radius of the circle.
 * @note Units in map space. Must call kv_destroy after use.
 */
EntityVector Scene_GetEntitiesArea(Scene* scene, Vector2 center, float radius);

#endif 