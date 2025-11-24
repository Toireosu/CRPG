#ifndef MAP_H
#define MAP_H

typedef struct Map {
    int width;
    int height;
    char* farground;
    char* background;
    char* midground;
    char* foreground;
} Map;

void Map_Create(Map* map);
void Map_Free(Map* map);

#endif