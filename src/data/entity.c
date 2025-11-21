#include "data/entity.h"

#include "raymath.h"

#define ENTITY_MOVE_SPEED 400

void Entity_Init(Entity* entity, EntityType type, Vector2 position) {
    entity->position = position;
    entity->target_index = entity->position;
    entity->size = (Vector2){ 16, 16 };
    entity->type = type;

    switch (type) {
        default:
        break; 
    }
}

void Entity_Tick(Entity* entity, float delta) {
    // Temp
    entity->position = Vector2Add(
        entity->position, 
        Vector2Scale(Vector2Normalize(Vector2Subtract(entity->target_index, entity->position)), 
        delta * ENTITY_MOVE_SPEED
    ));
}

void Entity_Move(Entity* entity, Vector2 index) {
    entity->target_index = index;
}