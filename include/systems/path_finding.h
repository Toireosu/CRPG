#ifndef PATH_FINDING_H
#define PATH_FINDING_H

#include "raylib.h"
#include <stdbool.h>
#include "data/scene.h"

void PathFinding_Build(Scene* scene);
bool PathFinding_ClaimIndex(Entity* entity, Vector2 position);
Vector2* PathFinding_FindPath(Vector2 from, Vector2 to);

#endif