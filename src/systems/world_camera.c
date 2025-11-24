#include "systems/world_camera.h"

#define TILE_SIZE (Vector2){32, 64}

Vector2 WorldCamera_MapToScreen(Vector2 v) {
    return (Vector2) {
        v.x * TILE_SIZE.x + v.y * TILE_SIZE.x,
        v.x * -TILE_SIZE.x / 2 + v.y * TILE_SIZE.x / 2
    };
}

Vector2 WorldCamera_ScreenToMap(Vector2 v) {
    return (Vector2) {
        v.x / (TILE_SIZE.x * 2) - (v.y / TILE_SIZE.x),
        v.x / (TILE_SIZE.x * 2) + v.y / TILE_SIZE.x
    };
}