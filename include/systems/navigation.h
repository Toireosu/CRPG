#ifndef PATH_FINDING_H
#define PATH_FINDING_H

#include "raylib.h"
#include <stdbool.h>
#include "data/scene.h"
#include "kvec.h"
#include "data/coordinates.h"

void Navigation_Init(const Map* map);
bool Navigation_OccupyTile(Entity* entity, Coordinates position);
NavPath Navigation_FindPath(Coordinates from, Coordinates to);

#endif