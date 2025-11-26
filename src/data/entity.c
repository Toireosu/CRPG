#include "data/entity.h"
#include "systems/path_finding.h"
#include <stdio.h>

#include "raymath.h"
#include "data/event_log.h"

#define ENTITY_MOVE_SPEED 2

void Entity_Init(Entity* entity, EntityType type, Coordinates position) {
    entity->position = Coordinates_ToVector2(position);
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

    
    Vector2 target_index = Coordinates_ToVector2(kv_A(entity->path->data.path, entity->path_index));
    Vector2 dir = Vector2Subtract(target_index, entity->position);
    Vector2 step =  Vector2Scale(Vector2Normalize(Vector2Subtract(target_index, entity->position)), delta * ENTITY_MOVE_SPEED);
    
    // Temp
    entity->position = Vector2Add(
        entity->position, 
        step
    );
    
    if (Vector2Length(dir) < 0.01) {
        entity->path_index--;
        printf("Target: %f, %f \n", target_index.x, target_index.y);
    }
    
    if (entity->path_index < 0) {
        kv_destroy(entity->path->data.path);
        entity->path->success = 0;
        entity->path->data.reason = "";
    }
}

void Entity_Move(Entity* entity, Coordinates coords) {
    // TODO: Print message if player 
    *entity->path = PathFinding_FindPath(Coordinates_FromVector2(entity->position), coords);
    
    if (entity->path->success) {
        entity->path_index = kv_size(entity->path->data.path) - 1;
    } else {
        EventLog_Push(entity->path->data.reason);
    }
}