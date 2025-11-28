#include "systems/navigation.h"

#include <stdlib.h>

#include "khash.h"
#include "kvec.h"
#include "ksort.h"
#include "raymath.h"
#include <stdio.h>
#include "data/map.h"

#define NAV_NODE_ADJACENT_COUNT 4

typedef struct NavGraphNode {
    bool exists;
    Entity* occupier;
    Coordinates coords;
    struct NavGraphNode* adjecent[NAV_NODE_ADJACENT_COUNT];
} NavGraphNode;

typedef struct NavSearchNode {
    int g; // distance from start 
    int h; // distance to end 
    int f; // sum
    struct NavSearchNode* parent;
    Coordinates coords;
} NavSearchNode;

static inline khint_t NavSearchNode_Hash(NavSearchNode* n);
static inline int NavSearchNode_Compare(const void* pa, const void* pb);
static inline int NavSearchNode_Equal(NavSearchNode* a, NavSearchNode* b);
static NavSearchNode* NavSearchNode_Create(NavGraphNode n, NavSearchNode* parent, Coordinates target_position);

typedef kvec_t(NavSearchNode) NavSearchNodeList;
typedef kvec_t(NavSearchNode*) NavOpenNodeList;

static NavSearchNodeList node_heap;

KHASH_INIT(NavSearchNodeSet, NavSearchNode*, char, false, NavSearchNode_Hash, NavSearchNode_Equal)

struct {
    int width;
    int height;
    NavGraphNode* nodes;
} navigation_graph;

static bool Navigation_CoordinatesOutside(Coordinates coords) {
    return coords.x < 0 || coords.y < 0 || coords.x >= navigation_graph.width || coords.y >= navigation_graph.height;
}

static NavGraphNode* Navigation_GetGraphNodeRef(Coordinates coords) {
    return &navigation_graph.nodes[coords.x + coords.y * navigation_graph.width];
}


static const int WALL_DIR_X[4] = { -1, +1,  0,  0 };
static const int WALL_DIR_Y[4] = {  0,  0, -1, +1 };
static const int WALL_OPPOSITE_INDEX[4] = { 1, 0, 3, 2 };

static void PathFinding_AddNode(const Map* map, int x, int y) {
    char id = Map_GetBackground(map, x, y);
    Coordinates coords = (Coordinates) { x, y };

    *Navigation_GetGraphNodeRef(coords) = (NavGraphNode) {
        .exists = id ? true : false,
        .occupier = NULL,
        .coords = coords,
    };

    for (int i = 0; i < NAV_NODE_ADJACENT_COUNT; i++)
        Navigation_GetGraphNodeRef(coords)->adjecent[i] = NULL;     
}

static void PathFinding_AddEdges(const Map* map, int x, int y) {
    Coordinates coords = (Coordinates) { x, y };

    NavGraphNode* node = Navigation_GetGraphNodeRef(coords);

    WallTile tile = Map_GetMidground(map, x, y);
    
    for (int i = 0; i < NAV_NODE_ADJACENT_COUNT; i++) {
        // Temp: how will we handle doors ?
        if (tile.ids[i]) continue;

        Coordinates adjacent_coords = (Coordinates) {
            .x = x + WALL_DIR_X[i],
            .y = y + WALL_DIR_Y[i],
        };

        if (Navigation_CoordinatesOutside(adjacent_coords)) continue;

        NavGraphNode* adjacent_node = Navigation_GetGraphNodeRef(adjacent_coords);

        if (adjacent_node->exists) {
            WallTile adjacent_tile = Map_GetMidground(map, adjacent_coords.x, adjacent_coords.y);

            if (adjacent_tile.ids[WALL_OPPOSITE_INDEX[i]]) continue;

            node->adjecent[i] = adjacent_node; 
        }
    }
}

void Navigation_Init() {
    kv_init(node_heap);
}

void Navigation_GenerateGraph(const Map* map) {
    int area = map->width * map->height;

    navigation_graph.width = map->width;
    navigation_graph.height = map->height;

    navigation_graph.nodes = calloc(area, sizeof(NavGraphNode));

    // put all tiles in nodes list
    Map_ForEachTile(map, PathFinding_AddNode(map, x, y));

    // add adjacent
    Map_ForEachTile(map, PathFinding_AddEdges(map, x, y));
}

bool Navigation_OccupyTile(Entity* entity, Coordinates coords) { 
    if (Navigation_CoordinatesOutside(coords)) return false;

    NavGraphNode* node = Navigation_GetGraphNodeRef(coords);
    if (node->occupier && node->occupier != entity) return false;

    if (!Navigation_CoordinatesOutside(entity->occupied_coord))
        Navigation_GetGraphNodeRef(entity->occupied_coord)->occupier = NULL;
    
    node->occupier = entity;
    entity->occupied_coord = coords;

    return true;
}

static int Navigation_Hueristic(Coordinates c0, Coordinates c1) {
    return roundl((abs(c1.x - c0.x) + abs(c1.y - c0.y)) * 0.8); 
}

static NavSearchNode* NavSearchNode_Create(NavGraphNode graph_node, NavSearchNode* parent, Coordinates target_coords) {
    int g = parent ? parent->g + 1 : 0;
    int h = Navigation_Hueristic(graph_node.coords, target_coords);
    
    NavSearchNode search_node = (NavSearchNode) {
        .g = g,
        .h = h,
        .f = g + h,
        .parent = parent,
        .coords = graph_node.coords,
    };

    kv_push(NavSearchNode, node_heap, search_node);

    return &kv_A(node_heap, kv_size(node_heap) - 1);
}

static inline khint_t NavSearchNode_Hash(NavSearchNode* node) {
    return 73856093 * node->coords.x ^ 19349663 * node->coords.y;
} 

static inline int NavSearchNode_Compare(const void* pa, const void* pb) {
    NavSearchNode *a = *(NavSearchNode**)pa;
    NavSearchNode *b = *(NavSearchNode**)pb;
    if (a->f > b->f) return -1;
    if (a->f < b->f) return 1;
    return 0;
} 

static inline int NavSearchNode_Equal(NavSearchNode* a, NavSearchNode* b) {
    return a->coords.x == b->coords.x &&
           a->coords.y == b->coords.y;
} 

static inline void Navigation_Free(NavOpenNodeList* open, khash_t(NavSearchNodeSet)** closed) {
    kh_destroy(NavSearchNodeSet, *closed);
    kv_destroy(*open);
}

static inline NavPath Navigation_GenerateNavPath(NavSearchNode* last_node) {
    NavPath path = (NavPath){ .success = true, };
            
    kv_init(path.data.path);
            
    NavSearchNode* node = last_node;
    while (node) {
        kv_push(Coordinates, path.data.path, node->coords);
        node = node->parent;
    }

    return path;
}

NavPath Navigation_FindPath(Coordinates from, Coordinates to) {
    if (Navigation_CoordinatesOutside(from)) return (NavPath){ .success = false, .data.reason = "Error: Entity outside of bounds!" };
    if (Navigation_CoordinatesOutside(to)) return (NavPath){ .success = false, .data.reason = "Can't get there!" };

    kv_size(node_heap) = 0;

    NavGraphNode from_node = *Navigation_GetGraphNodeRef(from); 
    NavGraphNode to_node = *Navigation_GetGraphNodeRef(to); 

    if (!from_node.exists) return (NavPath){ .success = false, .data.reason = "Error: Entity on non-nav tile!" };
    if (!to_node.exists) return (NavPath){ .success = false, .data.reason = "Can't get there!" };

    
    khash_t(NavSearchNodeSet) *closed = kh_init(NavSearchNodeSet);
    NavOpenNodeList open;
    kv_init(open);
    
    NavSearchNode* first = NavSearchNode_Create(from_node, NULL, to);
    kv_push(NavSearchNode*, open, first);

    while (kv_size(open) > 0) {
        qsort(open.a, kv_size(open), sizeof(NavSearchNode*), NavSearchNode_Compare);
        NavSearchNode* open_search_node = kv_pop(open);
        NavGraphNode current_m = *Navigation_GetGraphNodeRef(open_search_node->coords);
        
        // open.a[0] = open.a[kv_size(open) - 1];
        // kv_pop(open);
        int r;
        kh_put(NavSearchNodeSet, closed, open_search_node, &r);
        
        if (Coordinates_Equals(open_search_node->coords, to_node.coords)) {
            
            NavPath path = Navigation_GenerateNavPath(open_search_node);
            
            Navigation_Free(&open, &closed);
            
            return path;
        }

        for (int i = 0; i < NAV_NODE_ADJACENT_COUNT; i++) {
            NavGraphNode* sib_node = current_m.adjecent[i];

            if (!sib_node) continue;

            // If tile is occupied skip
            if (sib_node->occupier) continue;

            NavSearchNode* adjacent_node = NavSearchNode_Create(*sib_node, open_search_node, to);

            khiter_t it = kh_get(NavSearchNodeSet, closed, adjacent_node);
            if (it != kh_end(closed))
                continue;
            
            kv_push(NavSearchNode*, open, adjacent_node);
        }

    }

    Navigation_Free(&open, &closed);

    return (NavPath){ .success = false, .data.reason = "Can't get there!" };
}