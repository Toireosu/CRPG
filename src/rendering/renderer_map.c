#include "rendering/renderer.h"

#include "systems/scene_camera.h"
#include <string.h>

static const float WALL_X[4] = { -0.5, 0.5, 0, 0 };
static const float WALL_Y[4] = { 0, 0, -0.5, 0.5};
static const float WALL_Z[4] = { 1, -1, -1, 1};

// TODO: Should be precomputed?
// TODO: I am too lazy rn, make struct for this.
static int* roof_mask = NULL;
static int next_mask_index = 0;
static const int ROOF_X[4] = { -1, 1, 0, 0 };
static const int ROOF_Y[4] = { 0, 0, -1, 1 };

static void Renderer_RoofFlood(const Map* map, int x, int y) {
    if (Map_GetForeground(map, x, y)) {
        if (roof_mask[x + y * map->width] == -1) {
            roof_mask[x + y * map->width] = next_mask_index;
            for (int i = 0; i < 4; i++) {                
                Renderer_RoofFlood(map, x + ROOF_X[i], y + ROOF_Y[i]);
            }
        }
    }
}

void Renderer_MapInit(const Map* map) {
    if (roof_mask != NULL)
        free(roof_mask);

    int roof_mask_size = map->width * map->height * sizeof(int);
    roof_mask = malloc(roof_mask_size);
    for (int i = 0; i < map->width * map->height; i++) {
        roof_mask[i] = -1;
    }

    next_mask_index = 0;

    Map_ForEachTile(map,
    {
        if (Map_GetForeground(map, x, y)) {
            if (roof_mask[x + y * map->width] == -1) {
                Renderer_RoofFlood(map, x, y);
                next_mask_index++;
            }
        }
    });
}

static Vector2 Renderer_CalculateWallSegPosition(int x, int y, int i) {
    return SceneCamera_MapToScreen((Vector2){ x + WALL_X[i], y + WALL_Y[i] });
}

void Renderer_RenderMapForeground(const Scene* scene) {
    int px = scene->player->occupied_coord.x;
    int py = scene->player->occupied_coord.y;
    const Map* map = &scene->map;

    int player_roof_index = -1;
    if (Map_GetForeground(map, px, py))
        player_roof_index = roof_mask[px + py * map->width];

    Map_ForEachTile(map, {
        if (Map_GetForeground(map, x, y)) {
            if (roof_mask[x + y * map->width] == player_roof_index) continue;

            Vector2 position = SceneCamera_MapToScreen((Vector2){ x, y });

            DrawTexturePro(
                roof_texture, 
                (Rectangle){0, 0, 64, 32},
                (Rectangle){ position.x, position.y - 48, 64, 32 }, 
                (Vector2){ 32, 16 }, 
                0.0f,
                WHITE
            );
        }
    });
}

void Renderer_RenderMapBackground(const Map* map) {
    Map_ForEachTile(map, {
        if (Map_GetBackground(map, x, y)) {
            Vector2 position = SceneCamera_MapToScreen((Vector2){ x, y });

            DrawTexturePro(
                floor_texture, 
                (Rectangle){0, 0, 64, 32},
                (Rectangle){ position.x, position.y, 64, 32 }, 
                (Vector2){ 32, 16 }, 
                0.0f,
                WHITE
            );
        }
    });
}

void Renderer_CollectMapSprites(const Map* map) {
    Map_ForEachTile(map, {
        WallTile tile = Map_GetMidground(map, x, y);

        for (int i = 0; i < WALL_TILE_NUM_WALLS; i++) {
            if (!tile.ids[i]) continue;                

            Vector2 position = Renderer_CalculateWallSegPosition(x, y, i);

            Renderer_AddSprite((Sprite){
                .texture = wall_texture,
                .source = (Rectangle){
                    (tile.ids[i] - 1) * 32,
                    0,
                    32,
                    64
                },
                .position = position,
                .size = (Vector2){ 32, 64 },
                .origin = (Vector2){ 16, 56 },
                .z = Renderer_CalculateZ((Vector2){ x, y }) + WALL_Z[i],
            });
        }
    });
}