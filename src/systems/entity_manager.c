#include "systems/entity_manager.h"

#include "data/entity.h"

void EntityManager_Tick(Scene* scene, float delta) {
    if (!scene) return;

    for (int i = 0; i < scene->entities_count; i++) {
        Entity_Tick(&scene->entities[i], delta);
    }
}