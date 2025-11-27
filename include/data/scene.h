#ifndef SCENE_H
#define SCENE_H

#define SCENE_MAX_ENTITY_COUNT 100

#include "entity.h"
#include "map.h"

typedef struct Scene {
    Entity entities[SCENE_MAX_ENTITY_COUNT];
    int entities_count;
    Entity* player;
    Map map;
} Scene;

void Scene_Init(Scene* scene);
Entity* Scene_CreateEntity(Scene* scene);
void Scene_SetPlayer(Scene* scene, Entity* entity);

#endif 