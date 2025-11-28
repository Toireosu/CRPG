#include "systems/scene_camera.h"
#include "raymath.h"

#include "data/globals.h"

struct {
    Camera2D internal;
} camera_data;

void SceneCamera_Init() {
    camera_data.internal = (Camera2D) { 0 };
    camera_data.internal.zoom = 1;
    SceneCamera_Reset();
}

void SceneCamera_Reset() {
    camera_data.internal.target = (Vector2){ 0 };
}

Vector2 SceneCamera_MapToScreen(Vector2 v) {
    Vector2 pos = (Vector2) {
        v.x * TILE_SIZE.x + v.y * TILE_SIZE.x,
        v.x * -TILE_SIZE.x / 2 + v.y * TILE_SIZE.x / 2
    };
    return Vector2Subtract(pos, camera_data.internal.target);
}

Vector2 SceneCamera_ScreenToMap(Vector2 v) {
    v = Vector2Add(v, camera_data.internal.target);
    return (Vector2) {
        v.x / (TILE_SIZE.x * 2) - (v.y / TILE_SIZE.x),
        v.x / (TILE_SIZE.x * 2) + v.y / TILE_SIZE.x
    };
}

void SceneCamera_SetPosition(Vector2 v) {
    camera_data.internal.target = v;
}

void SceneCamera_Move(Vector2 v) {
    camera_data.internal.target = Vector2Add(camera_data.internal.target, Vector2Scale(v, GetFrameTime()));
}