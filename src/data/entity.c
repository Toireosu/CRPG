#include "data/entity.h"
#include "systems/path_finding.h"
#include <stdio.h>

#include "raymath.h"
#include "systems/event_log.h"

#define ENTITY_MOVE_MAX_VEL 2
#define ENTITY_SMOOTHING_FACTOR 21

static bool Entity_OccupyTile(Entity* entity, Coordinates coords) {
    bool result = PathFinding_ClaimIndex(entity, coords);
    entity->position = Coordinates_ToVector2(entity->occupied_coord);
    return result;
}

void Entity_Init(Entity* entity, EntityType type, Coordinates position) {
    entity->position = Coordinates_ToVector2(position);
    entity->velocity = (Vector2){ 0 };
    // Needed for OccupyTile logic
    entity->occupied_coord = (Coordinates){-1, -1};
    Entity_OccupyTile(entity, position);
    entity->path = malloc(sizeof(NavPath)); 
    *entity->path = (NavPath) { .success = false, .data.reason = "", };
    entity->size = (Vector2){ 16, 16 };
    entity->type = type;

    switch (type) {
        default:
        break; 
    }
}


void Entity_Free(Entity* entity) {
    free(entity->path);
}

void Entity_Tick(Entity* entity, float delta) {
    if (!entity->path->success) return;

    Coordinates target_coordinates = kv_A(entity->path->data.path, entity->path_index);
    Vector2 target_index = Coordinates_ToVector2(target_coordinates);
    Vector2 dir = Vector2Subtract(target_index, entity->position);

    Vector2 desired_vel = Vector2Scale(Vector2Normalize(dir), ENTITY_MOVE_MAX_VEL);

    entity->velocity = Vector2Lerp(entity->velocity, desired_vel, ENTITY_SMOOTHING_FACTOR * delta);

    entity->position = Vector2Add(entity->position, Vector2Scale(entity->velocity, delta));
    
    if (Vector2Length(dir) < 0.01) {
        entity->path_index--;

        if (!Entity_OccupyTile(entity, Coordinates_FromVector2(target_coordinates))) {
            entity->path_index = -1;
        }
        entity->position = Coordinates_ToVector2(entity->occupied_coord);
    }
    
    if (entity->path_index < 0) {
        kv_destroy(entity->path->data.path);
        entity->path->success = 0;
        entity->path->data.reason = "";
    }
}

void Entity_Move(Entity* entity, Coordinates coords) {
    *entity->path = PathFinding_FindPath(Coordinates_FromVector2(entity->position), coords);
    
    if (entity->path->success) {
        entity->path_index = kv_size(entity->path->data.path) - 1;
    } else {
        EventLog_Push(entity->path->data.reason);
    }
}