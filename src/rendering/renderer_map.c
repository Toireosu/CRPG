#include "rendering/renderer.h"

#include "systems/world_camera.h"

static const float WALL_X[4] = { -0.5, 0.5, 0, 0 };
static const float WALL_Y[4] = { 0, 0, -0.5, 0.5};
static const float WALL_Z[4] = { 1, -1, -1, 1};

static Vector2 Renderer_CalculateWallSegPosition(int x, int y, int i) {
    return WorldCamera_MapToScreen((Vector2){ x + WALL_X[i], y + WALL_Y[i] });
}

void Renderer_RenderMapBackground(const Map* map) {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (Map_GetBackground(map, x, y)) {
                Vector2 w_pos = WorldCamera_MapToScreen((Vector2){ x, y });

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

void Renderer_CollectMapSprites(const Map* map) {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            WallTile tile = Map_GetMidground(map, x, y);

            for (int i = 0; i < WALL_TILE_NUM_WALLS; i++) {
                if (!tile.ids[i]) continue;                

                Vector2 w_pos = Renderer_CalculateWallSegPosition(x, y, i);

                Renderer_AddSprite((Sprite){
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
                    .z = Renderer_CalculateZ((Vector2){ x, y }) + WALL_Z[i],
                });
            }

        }
    }
}