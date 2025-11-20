#include "data/entity.h"

void Entity_Init(Entity* entity, EntityType type, Vector2 position) {
    entity->position = position;
    entity->size = (Vector2){ 16, 16 };
    entity->type = type;

    switch (type) {
        default:
        break; 
    }
}