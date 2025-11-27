#ifndef MAP_H
#define MAP_H

#include "wall_tile.h"

typedef struct Map {
    int width;
    int height;
    char* farground;
    char* background;
    WallTile* midground;
    char* foreground;
} Map;

// Map must be freed with Map_Free after creation.
void Map_Create(Map* map, int width, int height);
void Map_Free(Map* map);

char Map_GetBackground(const Map* map, int x, int y);
void Map_SetBackground(Map* map, int x, int y, char id);

WallTile Map_GetMidground(const Map* map, int x, int y);
void Map_SetMidground(Map* map, int x, int y, int index, char id);

char Map_GetForeground(const Map* map, int x, int y);
void Map_SetForeground(Map* map, int x, int y, char id);

#endif