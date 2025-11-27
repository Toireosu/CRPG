#ifndef ENTITY_H
#define ENTITY_H

#include "data/renderable.h"
#include "raylib.h"
#include "data/coordinates.h"

typedef enum EntityType {
    ET_CHARACTER,
    ET_CRITTER,
    ET_OBJECT
} EntityType;

typedef struct NavPath NavPath;
typedef struct Entity {
    Vector2 position;
    Vector2 velocity;
    Coordinates occupied_coord;
    NavPath* path;
    int path_index;
    Vector2 size;
    // Renderable renderable;
    
    EntityType type;
} Entity;

void Entity_Init(Entity* entity, EntityType type, Coordinates position);
void Entity_Free(Entity* entity);
void Entity_Tick(Entity* entity, float delta);
void Entity_Move(Entity* entity, Coordinates coords);


#endif