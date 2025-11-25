#include "systems/path_finding.h"

#include <stdlib.h>

#define NAV_NODE_MAX_SIBS 4

typedef struct NavNode {
    bool skip;
    Vector2 position;
    struct NavNode* adjecent[NAV_NODE_MAX_SIBS];
} NavNode;

struct {
    int width;
    int height;
    NavNode* nodes;
} path_finding_data;

void PathFinding_Build(Scene* scene) {
    const Map* map = &scene->map;
    path_finding_data.width = map->width;
    path_finding_data.height = map->height;
    int area = map->width * map->height;

    path_finding_data.nodes = calloc(path_finding_data.width * path_finding_data.height, sizeof(NavNode));

    // put all tiles in nodes list

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            char id = Map_GetBackground(map, x, y);
    
            path_finding_data.nodes[x + y * map->width] = (NavNode) {
                .skip = id ? true : false,
                .position = (Vector2) { x, y },
            };

            // TODO: memset ??
            for (int i = 0; i < NAV_NODE_MAX_SIBS; i++)  
                path_finding_data.nodes[x + y * map->width].adjecent[i] = NULL;       
        }
    }

    // add adjacent
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            NavNode* node = &path_finding_data.nodes[x + y * map->width];

            WallTile n_tile = Map_GetMidground(map, x, y);
            
            // TODO: memset ??
            for (int i = 0; i < NAV_NODE_MAX_SIBS; i++) {
                
                int ix = i % 2; 
                int iy = i / 2; 
                
                // Temp: how will we handle doors ?
                if (n_tile.ids[i]) continue;

                int a_x = x + (ix * 2) - 1;
                int a_y = y + (iy * 2) - 1;

                if (a_x < 0 || a_y < 0 || a_x >= map->width || a_y >= map->height)
                    continue;

                NavNode* adj_node = &path_finding_data.nodes[a_x  + a_y * map->width];

                if (!adj_node->skip) {

                    WallTile a_tile = Map_GetMidground(map, x, y);

                    a_x = (ix + 1) % 2;
                    a_y = (iy + 1) % 2;

                    if (a_tile.ids[a_x + a_y * 2]) continue;

                    path_finding_data.nodes[x + y * map->width].adjecent[i] = adj_node; 
                }

            }
        }
    }
}

bool PathFinding_ClaimIndex(Entity* entity, Vector2 position) { /* TODO */ }

typedef struct NavBuildNode {
    float g; // distance from start 
    float h; // distance to end 
    float f; // sum
    NavBuildNode* parent;
} NavBuildNode;

Vector2* PathFinding_FindPath(Vector2 from, Vector2 to) {

}