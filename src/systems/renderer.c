#include "systems/renderer.h"
#include "data/map.h"
#include "data/event_log.h"
#include "systems/window_handler.h"
#include "raylib.h"
#include "systems/world_camera.h"

#include "assets/textures_precomped.h"

#include "raymath.h"
#include <stdlib.h>

static Texture floor_texture;
static Texture wall_texture;
static Texture character_texture;

typedef struct MidgroundSprite {
    Texture texture;
    Rectangle source;
    Vector2 position;
    Vector2 size;
    Vector2 origin;
    int z;
} MidgroundSprite;

struct MidgroundSpriteStack {
    MidgroundSprite* sprites;
    int count;
    int max_size;
} sprite_stack;

void Renderer_StackReset() {
    sprite_stack.count = 0;
}

int Renderer_CalculateZ(Vector2 coordinate) {
    return (coordinate.y - coordinate.x) * 2;
}

static void Renderer_AddSprite(MidgroundSprite sprite) {
    if (sprite_stack.count >= sprite_stack.max_size) {
        sprite_stack.max_size *= 2; 
        sprite_stack.sprites = realloc(sprite_stack.sprites, sprite_stack.max_size * sizeof(MidgroundSprite));
    }

    sprite_stack.sprites[sprite_stack.count] = sprite;
    sprite_stack.count++;
}

static void Renderer_Swap(MidgroundSprite* s0, MidgroundSprite* s1) {
    MidgroundSprite temp = *s0;
    *s0 = *s1;
    *s1 = temp; 
}

static int Renderer_Partition(int low, int high) {
    int pivot = sprite_stack.sprites[high].z;

    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (sprite_stack.sprites[j].z < pivot) {
            i++;
            Renderer_Swap(&sprite_stack.sprites[i], &sprite_stack.sprites[j]);
        }
    }

    Renderer_Swap(&sprite_stack.sprites[i + 1], &sprite_stack.sprites[high]);
    return i + 1;
}

static void Renderer_SortSprites(int low, int high) {
    if (low >= high)
        return;
        
    int partition = Renderer_Partition(low, high);
    
    Renderer_SortSprites(low, partition - 1);
    Renderer_SortSprites(partition + 1, high);
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

    sprite_stack.sprites = malloc(sizeof(MidgroundSprite) * 20);
    sprite_stack.count = 0;
    sprite_stack.max_size = 20;
}

static void Renderer_CollectEntities(const Scene* scene) {

    for (int i = 0; i < scene->entities_count; i++) {
        const Entity* entity = &scene->entities[i];
        Vector2 w_pos = WorldCamera_MapToScreen(entity->position);
    
        Renderer_AddSprite((MidgroundSprite){
            .texture = character_texture,
            .source = (Rectangle){
                0,
                0,
                32,
                64
            },
            .position = w_pos,
            .size = (Vector2){ 32, 64 },
            .origin = (Vector2){ 16, 64 },
            .z = Renderer_CalculateZ(entity->position),
        });
    }
}

static void Renderer_RenderMapBackground(const Map* map) {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (Map_GetBackground(map, x, y)) {
                Vector2 w_pos = WorldCamera_MapToScreen((Vector2){ x, y });
                // Temp
                DrawTexturePro(
                    floor_texture, 
                    (Rectangle){0, 0, 64, 32},
                    (Rectangle){ w_pos.x, w_pos.y, 64, 32 }, 
                    (Vector2){ 32, 16 }, 
                    0.0f,
                    WHITE
                );
            }
        }
    }
}

static const float DIR_X[4] = { -0.5, 0.5, 0, 0 };
static const float DIR_Y[4] = { 0, 0, -0.5, 0.5};
static const float DIR_Z[4] = { 1, -1, -1, 1};

static Vector2 Renderer_GetWallSegmentPosition(int index) {
    int x_m = index % 2;
    int y_m = index / 2;
    return (Vector2){ (x_m * 32) - 16, (y_m * 16) - 8};
}

static void Renderer_CollectMapMidground(const Map* map) {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            WallTile tile = Map_GetMidground(map, x, y);

            for (int i = 0; i < WALL_TILE_NUM_WALLS; i++) {
                if (!tile.ids[i]) continue;                
                Vector2 wall_seg_pos = Renderer_GetWallSegmentPosition(i);
                Vector2 w_pos = WorldCamera_MapToScreen((Vector2){ x + DIR_X[i], y + DIR_Y[i] });
                // w_pos = Vector2Add(w_pos, Renderer_GetWallSegmentPosition(i));

                Renderer_AddSprite((MidgroundSprite){
                    .texture = wall_texture,
                    .source = (Rectangle){
                        (tile.ids[i] - 1) * 32,
                        0,
                        32,
                        64
                    },
                    .position = w_pos,
                    .size = (Vector2){ 32, 64 },
                    .origin = (Vector2){ 16, 56 },
                    .z = Renderer_CalculateZ((Vector2){ x, y }) + DIR_Z[i],
                });
            }

        }
    }
}

static void Renderer_RenderMidgroundSprite(MidgroundSprite sprite) {
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
    for (int i = 0; i < sprite_stack.count; i++) {
        MidgroundSprite sprite = sprite_stack.sprites[i];
        Renderer_RenderMidgroundSprite(sprite);
    }
}

static void Renderer_RenderScene(Scene* scene) {
    if (!scene) return;

    Renderer_RenderMapBackground(&scene->map);


    // Restructure
    // Collect sprites (texture, position, size, z-index)
    // Sort by Z
    // Render by order

    Renderer_StackReset();

    Renderer_CollectEntities(scene);
    Renderer_CollectMapMidground(&scene->map);

    Renderer_SortSprites(0, sprite_stack.count - 1);

    Renderer_RenderMidground();
}

static void Renderer_RenderUI(Game* game) {
    // Temp
    for (int i = 0; i < EVENT_LOG_MAX_COUNT; i++) {
        DrawText(
            EventLog_Get(&game->event_log, i), 
            0,
            WINDOW_HANDLER_HEIGHT - i * 20,
            20,
            WHITE
        );
    }
}

void Renderer_RenderGame(Game* game) {

    BeginDrawing();

    ClearBackground(BLACK);

    Renderer_RenderScene(game->scene);

    Renderer_RenderUI(game);

    EndDrawing();
}