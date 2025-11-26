#ifndef WORLD_CAMERA_H
#define WORLD_CAMERA_H

#include "raylib.h"

void WorldCamera_Init();
void WorldCamera_Reset();

Vector2 WorldCamera_MapToScreen(Vector2 v);
Vector2 WorldCamera_ScreenToMap(Vector2 v);
void WorldCamera_SetPosition(Vector2 v);
void WorldCamera_Move(Vector2 v, float delta);

void WorldCamera_BeginMode2D();

#endif