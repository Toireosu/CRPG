#ifndef COORDINATES_H
#define COORDINATES_H

#include "raylib.h"
#include "math.h"
#include <stdlib.h>

typedef struct Coordinates {
    int x;
    int y;
} Coordinates;

#define Coordinates_ToVector2(c) (Vector2){ (float)c.x, (float)c.y }
#define Coordinates_FromVector2(v) (Coordinates){ roundl(v.x), roundl(v.y) } 

static inline bool Coordinates_Equals(Coordinates c, Coordinates other) {
    return c.x == other.x && c.y == other.y;
}

#endif