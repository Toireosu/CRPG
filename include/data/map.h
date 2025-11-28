#ifndef MAP_H
#define MAP_H

#include "wall_tile.h"

/**
 * @brief Data describing the layout of a walkable map.
 * @note for all tile layers 0 means it's "air". 
 */
typedef struct Map {
    int width;
    int height;
    char* farground;
    char* background;
    WallTile* midground;
    char* foreground;
} Map;

/**
 * @brief Helper function to do something for every index in a map.
 * 
 * @param map The map to loop through.
 * @param exp The expression to evoke for each index.
 * @note @p exp may use x and y coordinates in each iteration.
 */
#define Map_ForEachTile(map, exp) \
    do {\
        for (int y = 0; y < map->height; y++)\
            for (int x = 0; x < map->width; x++)\
                exp ;\
    } while(0)\

/**
 * @brief Creates a new map with all tiles set to 0.
 * 
 * @param map A pointer to store the created map.
 * @param width Horizontal size of the map.
 * @param height Vertical size of the map.
 */
// Map must be freed with Map_Free after creation.
void Map_Create(Map* map, int width, int height);

/**
 * @brief Frees any internal data of given map.
 * 
 * @param map The Map to be freed.
 */
void Map_Free(Map* map);

/**
 * @brief Gets tile id for a given coordinate pair in the background layer.
 * 
 * @param map The map to get tile from.
 * @param x X-coordinate of tile.
 * @param y Y-coordinate of tile.
 * @return Id of tile or zero if coordinates are out of bounds.
 */
char Map_GetBackground(const Map* map, int x, int y);

/**
 * @brief Sets a tile id for a given coordinate pair in the background layer.
 * 
 * @param map The Map in which to set tile id.
 * @param x X-coordinate of tile.
 * @param y Y-coordinate of tile.
 * @param id New tile id.
 */
void Map_SetBackground(Map* map, int x, int y, char id);

/**
 * @brief Gets wall ids for a given coordinate pair in the midground layer.
 * 
 * @param map The map to get tile from.
 * @param x X-coordinate of tile.
 * @param y Y-coordinate of tile.
 * @return A WallTile struct containing all 4 possible walls of a tile.
 */
WallTile Map_GetMidground(const Map* map, int x, int y);

/**
 * @brief Sets a wall id for a given coordinate pair and wall index in the midground layer.
 * 
 * @param map The Map in which to set tile id.
 * @param x X-coordinate of tile.
 * @param y Y-coordinate of tile.
 * @param index The index of wall to be set.
 * @param id New wall id.
 * @note Wall index are in order (left, right, top, bottom).
 */
void Map_SetMidground(Map* map, int x, int y, int index, char id);

/**
 * @brief Gets tile id for a given coordinate pair in the foreground layer.
 * 
 * @param map The map to get tile from.
 * @param x X-coordinate of tile.
 * @param y Y-coordinate of tile.
 * @return Id of tile or zero if coordinates are out of bounds.
 */
char Map_GetForeground(const Map* map, int x, int y);

/**
 * @brief Sets a tile id for a given coordinate pair in the foreground layer.
 * 
 * @param map The Map in which to set tile id.
 * @param x X-coordinate of tile.
 * @param y Y-coordinate of tile.
 * @param id New tile id.
 */
void Map_SetForeground(Map* map, int x, int y, char id);

#endif