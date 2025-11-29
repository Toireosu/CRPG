#include "rendering/renderer.h"

#include "assets/textures_precomped.h"
#include "kvec.h"
#include "systems/engine.h"

Texture floor_texture;
Texture wall_texture;
Texture character_texture;
Texture roof_texture;

static kvec_t(Sprite) sprites;

static void Renderer_RenderSprite(Sprite sprite) {
    DrawTexturePro(
        sprite.texture,
        sprite.source,
        (Rectangle) {sprite.position.x, sprite.position.y, sprite.size.x, sprite.size.y },
        sprite.origin,
        0,
        WHITE
    );
}

static void Renderer_RenderMidground() {
    for (int i = 0; i < kv_size(sprites); i++) {
        Sprite sprite = kv_A(sprites, i);
        Renderer_RenderSprite(sprite);
    }
}

static inline int Renderer_CompareSprite(const void* pa, const void* pb) {
    Sprite a = *(Sprite*)pa;
    Sprite b = *(Sprite*)pb;
    return a.z - b.z;
} 

static void Renderer_RenderScene(Scene* scene) {
    if (!scene) return;

    Renderer_RenderMapBackground(&scene->map);

    kv_size(sprites) = 0;

    Renderer_CollectEntitySprites(scene);
    Renderer_CollectMapSprites(&scene->map);

    qsort(sprites.a, kv_size(sprites), sizeof(Sprite), Renderer_CompareSprite);

    Renderer_RenderMidground();

    Renderer_RenderMapForeground(scene);
}

void Renderer_Init() {
    Image floor_image = LoadImageFromMemory(".png", precomped_texture_floors, sizeof(precomped_texture_floors));
    floor_texture = LoadTextureFromImage(floor_image);
    UnloadImage(floor_image);

    Image wall_image = LoadImageFromMemory(".png", precomped_texture_walls, sizeof(precomped_texture_walls));
    wall_texture = LoadTextureFromImage(wall_image);
    UnloadImage(wall_image);

    Image character_image = LoadImageFromMemory(".png", precomped_texture_character, sizeof(precomped_texture_character));
    character_texture = LoadTextureFromImage(character_image);
    UnloadImage(character_image);

    Image roof_image = LoadImageFromMemory(".png", precomped_texture_roofs, sizeof(precomped_texture_roofs));
    roof_texture = LoadTextureFromImage(roof_image);
    UnloadImage(roof_image);

    kv_init(sprites);
    // Empty
    kv_size(sprites) = 0;
}

void Renderer_AddSprite(Sprite sprite) {
    kv_push(Sprite, sprites, sprite);
}

int Renderer_CalculateZ(Vector2 position) {
    Coordinates coords = Coordinates_FromVector2(position);
    return (coords.y - coords.x) * 2;
}

void Renderer_Render() {
    BeginDrawing();

    ClearBackground(BLACK);

    if (Engine_GetGameState() == GS_GAME)
        Renderer_RenderScene(Engine_GetScene());

    Renderer_RenderUI();

    EndDrawing();
}