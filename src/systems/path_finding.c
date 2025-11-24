#include "systems/path_finding.h"

#include <stdlib.h>

#define NAV_NODE_MAX_SIBS 4

typedef struct NavNode {
    Vector2 position;
    struct NavNode* adjecent[NAV_NODE_MAX_SIBS];
} NavNode;

struct PathFinding {
    int width;
    int height;
    NavNode* nodes;
} path_finding_data;

void PathFinding_Build(Scene* scene) {
    const Map* map = &scene->map;
    path_finding_data.width = map->width;
    path_finding_data.height = map->height;

    path_finding_data.nodes = calloc(path_finding_data.width * path_finding_data.height, sizeof(NavNode));


}

bool PathFinding_ClaimIndex(Entity* entity, Vector2 position) {}
Vector2* PathFinding_FindPath(Vector2 from, Vector2 to) {}