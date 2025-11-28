#include "data/entity.h"
#include "systems/navigation.h"
#include <stdio.h>

#include "raymath.h"
#include "systems/message_log.h"

#define ENTITY_MOVE_MAX_VEL 2
#define ENTITY_SMOOTHING_FACTOR 21

static void Entity_SnapPosition(Entity* entity) {
    entity->position = Coordinates_ToVector2(entity->occupied_coord);
}

static bool Entity_OccupyTile(Entity* entity, Coordinates coords) {
    bool result = Navigation_OccupyTile(entity, coords);
    Entity_SnapPosition(entity);
    return result;
}

static void Entity_NavPathReset(Entity* entity) {
    if (entity->path.success)
        kv_destroy(entity->path.data.path);

    entity->path.success = false;
    entity->path.data.reason = "";
}

void Entity_Init(Entity* entity, EntityType type, Coordinates position) {
    // Maybe not needed?
    entity->position = Coordinates_ToVector2(position);
    entity->velocity = (Vector2){ 0 };

    entity->occupied_coord = (Coordinates){-1, -1};
    Entity_OccupyTile(entity, position);
    Entity_NavPathReset(entity);

    entity->size = (Vector2){ 16, 16 };
    entity->type = type;

    switch (type) {
        default:
        break; 
    }
}

// Remove
void Entity_Free(Entity* entity) {
    Entity_NavPathReset(entity);
}

void Entity_Move(Entity* entity, float delta) {
    Coordinates next_coordinates = kv_A(entity->path.data.path, entity->path_index);
    Vector2 next_position = Coordinates_ToVector2(next_coordinates);
    Vector2 direction = Vector2Subtract(next_position, entity->position);

    Vector2 desired_velocity = Vector2Scale(Vector2Normalize(direction), ENTITY_MOVE_MAX_VEL);

    entity->velocity = Vector2Lerp(entity->velocity, desired_velocity, ENTITY_SMOOTHING_FACTOR * delta);
    entity->position = Vector2Add(entity->position, Vector2Scale(entity->velocity, delta));
    
    // Switch to next coordinate threshold
    if (Vector2Length(direction) < 0.01) {
        entity->path_index--;

        if (!Entity_OccupyTile(entity, Coordinates_FromVector2(next_coordinates))) 
            Entity_NavPathReset(entity);

        if (entity->path_index < 0)
            Entity_NavPathReset(entity);
        
        Entity_SnapPosition(entity);
    }
}

void Entity_Tick(Entity* entity) {
    if (entity->path.success)
        Entity_Move(entity, GetFrameTime());
}

void Entity_BeginMove(Entity* entity, Coordinates coords) {
    Entity_NavPathReset(entity);
    entity->path = Navigation_FindPath(Coordinates_FromVector2(entity->position), coords);
    
    if (entity->path.success) {
        entity->path_index = kv_size(entity->path.data.path) - 1;
    } else {
        MessageLog_Push(entity->path.data.reason);
    }
}