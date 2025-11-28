#include "rendering/renderer.h"

#include "systems/scene_camera.h"

void Renderer_CollectEntitySprites(const Scene* scene) {

    for (int i = 0; i < scene->entities_count; i++) {
        const Entity* entity = &scene->entities[i];
        Vector2 position = SceneCamera_MapToScreen(entity->position);
    
        Renderer_AddSprite((Sprite){
            .texture = character_texture,
            .source = (Rectangle){
                0,
                0,
                32,
                64
            },
            .position = position,
            .size = (Vector2){ 32, 64 },
            .origin = (Vector2){ 16, 64 },
            .z = Renderer_CalculateZ(entity->position),
        });
    }
}