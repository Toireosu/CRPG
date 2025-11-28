#ifndef SCENE_CAMERA_H
#define SCENE_CAMERA_H

#include "raylib.h"

void SceneCamera_Init();
void SceneCamera_Reset();

Vector2 SceneCamera_MapToScreen(Vector2 v);
Vector2 SceneCamera_ScreenToMap(Vector2 v);
void SceneCamera_SetPosition(Vector2 v);
void SceneCamera_Move(Vector2 v, float delta);

void SceneCamera_BeginMode2D();

#endif