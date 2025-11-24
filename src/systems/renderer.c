#include "systems/renderer.h"
#include "data/map.h"
#include "data/event_log.h"
#include "systems/window_handler.h"
#include "raylib.h"
#include "systems/world_camera.h"

#include "assets/textures_precomped.h"

#include "raymath.h"

static Texture floor_texture;
static Texture wall_texture;

void Renderer_Init() {

    Image floor_image = LoadImageFromMemory(".png", precomped_texture_floors, sizeof(precomped_texture_floors));
    floor_texture = LoadTextureFromImage(floor_image);
    UnloadImage(floor_image);

    Image wall_image = LoadImageFromMemory(".png", precomped_texture_walls, sizeof(precomped_texture_walls));
    wall_texture = LoadTextureFromImage(wall_image);
    UnloadImage(wall_image);
}

static void Renderer_RenderEntity(const Entity* entity) {
    Vector2 w_pos = WorldCamera_MapToScreen(entity->position);

    DrawRectangle(
        w_pos.x,
        w_pos.y,
        16,
        16,
        RED
    );
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

static Vector2 Renderer_GetWallSegmentPosition(int index) {
    int x_m = index % 2;
    int y_m = index / 2;
    return (Vector2){ (x_m * 32) - 16, (y_m * 16) - 8};
}

static void Renderer_RenderMapMidground(const Map* map) {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            WallTile tile = Map_GetMidground(map, x, y);

            for (int i = 0; i < WALL_TILE_NUM_WALLS; i++) {
                if (!tile.ids[i]) continue;                
                Vector2 wall_seg_pos = Renderer_GetWallSegmentPosition(i);
                Vector2 w_pos = WorldCamera_MapToScreen((Vector2){ x, y });
                w_pos = Vector2Add(w_pos, Renderer_GetWallSegmentPosition(i));
                
                // Temp
                DrawTexturePro(
                    wall_texture,
                    (Rectangle) { (i - 1) * 32, 0, 32, 64 },
                    (Rectangle) { w_pos.x, w_pos.y, 32, 64 },
                    (Vector2) {16, 56},
                    0,
                    WHITE
                );
            }

        }
    }
}

static void Renderer_RenderScene(Scene* scene) {
    if (!scene) return;

    Renderer_RenderMapBackground(&scene->map);

    Renderer_RenderMapMidground(&scene->map);

    for (int i = 0; i < scene->entities_count; i++) {
        Entity* entity = &scene->entities[i];
         
        Renderer_RenderEntity(entity);
    }
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