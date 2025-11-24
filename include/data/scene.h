#ifndef SCENE_H
#define SCENE_H

#define SCENE_MAX_ENTITY_COUNT 100

#include "entity.h"
#include "map.h"

typedef struct Scene {
    Entity entities[SCENE_MAX_ENTITY_COUNT];
    int entities_count;
    Map map;
} Scene;

void Scene_Init(Scene* scene);
void Scene_Add(Scene* scene, Entity entity);

#endif 