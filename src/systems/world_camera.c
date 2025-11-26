#include "systems/world_camera.h"
#include "raymath.h"

#define TILE_SIZE (Vector2){32, 64}

struct {
    Camera2D internal;
} camera_data;

void WorldCamera_Init() {
    camera_data.internal = (Camera2D) { 0 };
    camera_data.internal.zoom = 1;
    WorldCamera_Reset();
}

void WorldCamera_Reset() {
    camera_data.internal.target = (Vector2){ 0 };
}

Vector2 WorldCamera_MapToScreen(Vector2 v) {
    Vector2 pos = (Vector2) {
        v.x * TILE_SIZE.x + v.y * TILE_SIZE.x,
        v.x * -TILE_SIZE.x / 2 + v.y * TILE_SIZE.x / 2
    };
    return Vector2Subtract(pos, camera_data.internal.target);
}

Vector2 WorldCamera_ScreenToMap(Vector2 v) {
    v = Vector2Add(v, camera_data.internal.target);
    return (Vector2) {
        v.x / (TILE_SIZE.x * 2) - (v.y / TILE_SIZE.x),
        v.x / (TILE_SIZE.x * 2) + v.y / TILE_SIZE.x
    };
}

void WorldCamera_SetPosition(Vector2 v) {
    camera_data.internal.target = v;
}

void WorldCamera_Move(Vector2 v, float delta) {
    camera_data.internal.target = Vector2Add(camera_data.internal.target, Vector2Scale(v, delta));
}