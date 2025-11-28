#ifndef ENTITY_H
#define ENTITY_H

#include "data/renderable.h"
#include "raylib.h"
#include "data/coordinates.h"
#include "data/nav_path.h"

/**
 * @brief Type of entities. 
 */
typedef enum EntityType {
    ET_CHARACTER,
    ET_CRITTER,
    ET_OBJECT,
    ET_COUNT
} EntityType;

/**
 * @brief Entity data shared for all types as well specific type data.
 */
typedef struct Entity {
    Vector2 position;
    Vector2 velocity;
    Coordinates occupied_coord;
    NavPath path;
    int path_index;
    Vector2 size;
    // Renderable renderable;
    
    EntityType type;
} Entity;

/**
 * @brief Initializes a given entity.
 * 
 * @param entity A pointer to the entity to initialize.
 * @param type The type of entity to be initialized.
 * @param coords The position where the entity should be placed.
 */
void Entity_Init(Entity* entity, EntityType type, Coordinates coords);

/**
 * @brief Deallocates all heap allocated data used by entity.
 * @param entity The entity to free.
 */
void Entity_Free(Entity* entity);

/**
 * @brief Handles per frame updates for entity.
 * @param entity The entity to update.
 */
void Entity_Tick(Entity* entity);

/**
 * @brief Sets movement target for given entity.
 * @param entity The entity to move.
 * @param coords A coordinate pair the entity should move to.
 */
void Entity_BeginMove(Entity* entity, Coordinates coords);


#endif