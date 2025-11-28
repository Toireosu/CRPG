#ifndef COORDINATES_H
#define COORDINATES_H

#include "raylib.h"
#include "math.h"
#include <stdlib.h>

/**
 * @brief Integer coordinates pair (x, y).
 */
typedef struct Coordinates {
    int x;
    int y;
} Coordinates;

/**
 * @brief Converts integer Coordinates to a Vector2.
 * 
 * @param c The Coordinates to convert.
 * @return a Vector2 containing the same value pair as @p c.
 */
#define Coordinates_ToVector2(c) (Vector2){ (float)c.x, (float)c.y }

/**
 * @brief Converts a Vector2 to integer Coordinates.
 * 
 * @param v The Vector2 to convert.
 * @return Coordinates containing the rounded values of @p v.
 */
#define Coordinates_FromVector2(v) (Coordinates){ roundl(v.x), roundl(v.y) } 

/**
 * @brief Checks if two coordinate pairs are equal.
 * 
 * @param c First coordinates.
 * @param other Second coordinates.
 * @return true if coordinates are equal, false if not.  
 */
static inline bool Coordinates_Equals(Coordinates c, Coordinates other) {
    return c.x == other.x && c.y == other.y;
}

#endif