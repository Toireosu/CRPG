#include "data/map.h"

#include <stdlib.h>

void Map_Create(Map* map, int width, int height) {
    int map_area = width * height;
    map->farground = calloc(map_area, sizeof(char));
    map->background = calloc(map_area, sizeof(char));
    map->midground = calloc(map_area, sizeof(char));
    map->foreground = calloc(map_area, sizeof(char));
}

void Map_Free(Map* map) {
    free(map->farground);
    free(map->background);
    free(map->midground);
    free(map->foreground);
}