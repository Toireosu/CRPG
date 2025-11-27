#include "systems/path_finding.h"

#include <stdlib.h>

#include "khash.h"
#include "kvec.h"
#include "ksort.h"
#include "raymath.h"
#include <stdio.h>

#define NAV_NODE_MAX_SIBS 4

typedef struct NavNode {
    bool skip;
    Entity* occupier;
    Coordinates position;
    struct NavNode* adjecent[NAV_NODE_MAX_SIBS];
} NavNode;

struct {
    int width;
    int height;
    NavNode* nodes;
} path_finding_data;

static bool PathFinding_PositionIsOutside(Coordinates coords) {
    return coords.x < 0 || coords.y < 0 || coords.x >= path_finding_data.width || coords.y >= path_finding_data.height;
}

static const int DIR_X[4] = { -1, +1,  0,  0 };
static const int DIR_Y[4] = {  0,  0, -1, +1 };
static const int OPPOSITE[4] = { 1, 0, 3, 2 };

void PathFinding_Build(Scene* scene) {
    const Map* map = &scene->map;
    path_finding_data.width = map->width;
    path_finding_data.height = map->height;
    int area = map->width * map->height;

    path_finding_data.nodes = calloc(area, sizeof(NavNode));

    // put all tiles in nodes list

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            char id = Map_GetBackground(map, x, y);
    
            path_finding_data.nodes[x + y * map->width] = (NavNode) {
                .skip = id ? false : true,
                .occupier = NULL,
                .position = (Coordinates) { x, y },
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
                // Temp: how will we handle doors ?
                if (n_tile.ids[i]) continue;

                int a_x = x + DIR_X[i];
                int a_y = y + DIR_Y[i];

                if (a_x < 0 || a_y < 0 || a_x >= map->width || a_y >= map->height)
                    continue;

                NavNode* adj_node = &path_finding_data.nodes[a_x  + a_y * map->width];

                if (!adj_node->skip) {

                    WallTile a_tile = Map_GetMidground(map, a_x, a_y);

                    if (a_tile.ids[OPPOSITE[i]]) continue;

                    path_finding_data.nodes[x + y * map->width].adjecent[i] = adj_node; 
                }

            }
        }
    }
}

bool PathFinding_ClaimIndex(Entity* entity, Coordinates coords) { 
    if (PathFinding_PositionIsOutside(coords)) return false;
    NavNode* node = &path_finding_data.nodes[coords.x + coords.y * path_finding_data.width];
    if (node->occupier && node->occupier != entity) return false;

    if (PathFinding_PositionIsOutside(entity->occupied_coord)) {
        path_finding_data.nodes[entity->occupied_coord.x + entity->occupied_coord.y * path_finding_data.width].occupier = NULL;
    }
    node->occupier = entity;
    entity->occupied_coord = coords;
    return true;
}

typedef struct NavBuildNode {
    int g; // distance from start 
    int h; // distance to end 
    int f; // sum
    struct NavBuildNode* parent;
    Coordinates position;
} NavBuildNode;

static int Navigation_Hueristic(Coordinates c0, Coordinates c1) {
    return roundl((abs(c1.x - c0.x) + abs(c1.y - c1.x)) * 0.8); 
}

static NavBuildNode* NavBuildNode_New(NavNode n, NavBuildNode* parent, Coordinates target_position) {
    NavBuildNode* nbn = malloc(sizeof(NavBuildNode));
    nbn->g = parent ? parent->g + 1 : 0;
    nbn->h = Navigation_Hueristic(n.position, target_position);
    nbn->f = nbn->g + nbn->h;
    nbn->parent = parent;
    nbn->position = n.position;
    return nbn;
}

static inline khint_t NavNode_Hash(NavBuildNode* n) {
    return 73856093 * ((int)n->position.x) ^ 19349663 * ((int)n->position.y);
} 

static inline int NavNode_Compare(const void* pa, const void* pb) {
    NavBuildNode *a = *(NavBuildNode**)pa;
    NavBuildNode *b = *(NavBuildNode**)pb;
    if (a->f < b->f) return -1;
    if (a->f > b->f) return 1;
    return 0;
} 

static inline int NavNode_Equal(NavBuildNode* a, NavBuildNode* b) {
    return a->position.x == b->position.x &&
           a->position.y == b->position.y;
} 

KHASH_INIT(NavNodeSet, NavBuildNode*, char, false, NavNode_Hash, NavNode_Equal)

NavPath PathFinding_FindPath(Coordinates from, Coordinates to) {
    if (PathFinding_PositionIsOutside(from)) return (NavPath){ .success = false, .data.reason = "Error: Entity outside of bounds!" };
    if (PathFinding_PositionIsOutside(to)) return (NavPath){ .success = false, .data.reason = "Can't get there!" };;

    NavNode from_node = path_finding_data.nodes[(int)from.x + (int)from.y * path_finding_data.width]; 
    NavNode to_node = path_finding_data.nodes[(int)to.x + (int)to.y * path_finding_data.width]; 

    if (from_node.skip) return (NavPath){ .success = false, .data.reason = "Error: Entity on non-nav tile!" };
    if (to_node.skip) return (NavPath){ .success = false, .data.reason = "Can't get there!" };

    
    khash_t(NavNodeSet) *closed = kh_init(NavNodeSet);
    kvec_t(NavBuildNode*) open;
    kv_init(open);
    
    
    kv_push(NavBuildNode*, open, NavBuildNode_New(from_node, NULL, to));
    printf("From: %f, %f\n", from_node.position.x, from_node.position.y);
    printf("To: %f, %f\n", to_node.position.x, to_node.position.y);
    // Maybe we could allocat memory on stack for all potential node? And then migrate them to heap later?

    while (kv_size(open) > 0) {
        qsort(open.a, kv_size(open), sizeof(NavBuildNode*), NavNode_Compare);
        NavBuildNode* current = open.a[0];
        NavNode current_m = path_finding_data.nodes[(int)current->position.x + (int)current->position.y * path_finding_data.width];
        
        
        open.a[0] = open.a[kv_size(open) - 1];
        kv_pop(open);
        int r;
        kh_put(NavNodeSet, closed, current, &r);
        
        if (Coordinates_Equals(current->position, to_node.position)) {
            // Rebuild path and return
            // Free all used data
            
            
            // Remove all needed nodes from closed
            
            NavPath path = (NavPath){ 
                .success = true, 
            };
            
            kv_init(path.data.path);
            
            while (current) {
                kv_push(Coordinates, path.data.path, current->position);
                current = current->parent;
            }
            
            for (int i = 0; i < kv_size(open); i++) free(open.a[i]);
            kv_destroy(open);
            
            NavBuildNode* k;
            char v;
            // kh_foreach(closed, k, v, free(k));
            kh_destroy(NavNodeSet, closed);
            
            return path;
        }

        for (int i = 0; i < NAV_NODE_MAX_SIBS; i++) {
            NavNode* sib_node = current_m.adjecent[i];

            if (!sib_node) continue;

            // If tile is occupied skip
            if (sib_node->occupier) continue;

            NavBuildNode* sbn = NavBuildNode_New(*sib_node, current, to);

            khiter_t it = kh_get(NavNodeSet, closed, sbn);
            if (it != kh_end(closed)) {
                free(sbn);
                continue;
            }
            
            kv_push(NavBuildNode*, open, sbn);
        }

    }

    for (int i = 0; i < kv_size(open); i++) free(open.a[i]);
    NavBuildNode* k;
    char v;
    // kh_foreach(closed, k, v, { free(k); });

    kv_destroy(open);
    kh_destroy(NavNodeSet, closed);

    return (NavPath){ .success = false, .data.reason = "Can't get there!" };
}