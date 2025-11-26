#ifndef PATH_FINDING_H
#define PATH_FINDING_H

#include "raylib.h"
#include <stdbool.h>
#include "data/scene.h"
#include "kvec.h"
#include "data/coordinates.h"

typedef struct NavPath {
    bool success;
    union {
        kvec_t(Coordinates) path;
        const char* reason;
    } data;
} NavPath;

void PathFinding_Build(Scene* scene);
bool PathFinding_ClaimIndex(Entity* entity, Coordinates position);
NavPath PathFinding_FindPath(Coordinates from, Coordinates to);

#endif