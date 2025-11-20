#include "data/scene.h"

void Scene_Init(Scene* scene) {
    scene->entities_count = 0;
}

void Scene_Add(Scene* scene, Entity entity) {
    scene->entities[scene->entities_count] = entity;
    scene->entities_count += 1;
}