#include "data/scene.h"

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