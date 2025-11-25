#ifndef ENTITY_H
#define ENTITY_H

#include "renderable.h"
#include "raylib.h"

typedef enum EntityType {
    ET_CHARACTER,
    ET_CRITTER,
    ET_OBJECT
} EntityType;

typedef struct NavPath NavPath;
typedef struct Entity {
    Vector2 position;
    NavPath* path;
    int path_index;
    Vector2 size;
    // Renderable renderable;
    
    EntityType type;
} Entity;

void Entity_Init(Entity* entity, EntityType type, Vector2 position);
void Entity_Free(Entity* entity);
void Entity_Tick(Entity* entity, float delta);
void Entity_Move(Entity* entity, Vector2 index);


#endif