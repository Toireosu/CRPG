#ifndef SCENE_CAMERA_H
#define SCENE_CAMERA_H

#include "raylib.h"

/**
 * @brief Initializes the camera for rendering.
 */
void SceneCamera_Init();

/**
 * @brief Resets the cameras position.
 * @todo Remove: Redundant.
 */
void SceneCamera_Reset();

/**
 * @brief Converts a position in map space to screen space.
 * 
 * @param v The vector in map space to be converted.
 * @return A converted vector in screen space. 
 */
Vector2 SceneCamera_MapToScreen(Vector2 v);

/**
 * @brief Converts a position in screen space to map space.
 * 
 * @param v The vector in screen space to be converted.
 * @return A converted vector in map space. 
 */
Vector2 SceneCamera_ScreenToMap(Vector2 v);

/**
 * @brief Sets the target position of the camera.
 * 
 * @param v The new position for camera.
 */
void SceneCamera_SetPosition(Vector2 v);

/**
 * @brief Moves the camera in given direction.
 * 
 * @param v The direction and magnitude to move.
 * @param delta Delta time.
 */
void SceneCamera_Move(Vector2 v);

#endif