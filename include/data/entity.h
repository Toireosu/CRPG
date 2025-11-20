#ifndef ENTITY_H
#define ENTITY_H

#include "renderable.h"
#include "raylib.h"

typedef enum EntityType {
    ET_CHARACTER,
    ET_CRITTER,
    ET_OBJECT
} EntityType;

typedef struct Entity {
    Vector2 position;
    Vector2 size;
    // Renderable renderable;
    
    EntityType type;
} Entity;

void Entity_Init(Entity* entity, EntityType type, Vector2 position);

#endif