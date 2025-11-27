#include "data/map.h"

#include <stdlib.h>
#include <stdbool.h>

void Map_Create(Map* map, int width, int height) {
    int map_area = width * height;
    map->width = width;
    map->height = height;
    map->farground = calloc(map_area, sizeof(char));
    map->background = calloc(map_area, sizeof(char));
    map->midground = calloc(map_area, sizeof(WallTile));
    map->foreground = calloc(map_area, sizeof(char));
}

void Map_Free(Map* map) {
    free(map->farground);
    free(map->background);
    free(map->midground);
    free(map->foreground);
}

static bool Map_OutOfBounds(const Map* map, int x, int y) {
    return x < 0 || y < 0 || x >= map->width || y >= map->height;
}

char Map_GetBackground(const Map* map, int x, int y) {
    if (Map_OutOfBounds(map, x, y))
        return 0;

    return map->background[x + y * map->width];
}

void Map_SetBackground(Map* map, int x, int y, char id) {
    if (Map_OutOfBounds(map, x, y))
        return;

    map->background[x + y * map->width] = id;
}

WallTile Map_GetMidground(const Map* map, int x, int y) {
    if (Map_OutOfBounds(map, x, y))
        return WALL_TILE_EMPTY;

    return map->midground[x + y * map->width];
}

void Map_SetMidground(Map* map, int x, int y, int index, char id) {
    if (Map_OutOfBounds(map, x, y))
        return;

    map->midground[x + y * map->width].ids[index] = id;
}

char Map_GetForeground(const Map* map, int x, int y) {
    if (Map_OutOfBounds(map, x, y))
        return 0;

    return map->foreground[x + y * map->width];
}

void Map_SetForeground(Map* map, int x, int y, char id) {
    if (Map_OutOfBounds(map, x, y))
        return;

    map->foreground[x + y * map->width] = id;
}