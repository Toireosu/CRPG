#include "data/scene.h"
#include "raymath.h"

void Scene_Init(Scene* scene) {
    scene->entities_count = 0;
    Map_Create(&scene->map, 10, 10);
}

Entity* Scene_CreateEntity(Scene* scene) {
    return &scene->entities[scene->entities_count++];
}

void Scene_SetPlayer(Scene* scene, Entity* entity) {
    scene->player = entity;
}

EntityVector Scene_GetEntitiesArea(Scene* scene, Vector2 center, float radius) {
    EntityVector result;
    kv_init(result);

    for (int i = 0; i < scene->entities_count; i++) {
        Entity* entity = &scene->entities[i];
        float distance = Vector2Distance(entity->position, center);
        if (distance < radius) {
            kv_push(Entity*, result, entity);
        }
    }

    return result;
}
