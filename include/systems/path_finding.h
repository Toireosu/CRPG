#ifndef PATH_FINDING_H
#define PATH_FINDING_H

#include "raylib.h"
#include <stdbool.h>
#include "data/scene.h"
#include "kvec.h"

typedef struct NavPath {
    bool success;
    union {
        kvec_t(Vector2) path;
        const char* reason;
    } data;
} NavPath;

void PathFinding_Build(Scene* scene);
bool PathFinding_ClaimIndex(Entity* entity, Vector2 position);
NavPath PathFinding_FindPath(Vector2 from, Vector2 to);

#endif