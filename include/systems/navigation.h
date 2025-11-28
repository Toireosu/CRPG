#ifndef PATH_FINDING_H
#define PATH_FINDING_H

#include "raylib.h"
#include <stdbool.h>
#include "data/scene.h"
#include "kvec.h"
#include "data/coordinates.h"


/**
 * @brief Intializes the navigation system.
 */
void Navigation_Init();


/**
 * @brief Generates the navigation graph for the given map.
 * 
 * @param map The map from which to generate navigation data.
 * @note This should be run everytime a new scene is loaded.
 */
void Navigation_GenerateGraph(const Map* map);

/**
 * @brief Tries to set a tile as occupied by given entity.
 * 
 * @param entity The entity that will occupy the tile.
 * @param coords The coordinates to occupy.
 * @return True if entity was able to occupy tile, false otherwise.
 */
bool Navigation_OccupyTile(Entity* entity, Coordinates coords);

/**
 * @brief Finds a path from one coordinate pair to another.
 * 
 * @param from The coordinates to find path from.
 * @param to The target coordinates to find path to.
 * @return A NavPath struct containing success flag set to true and the found path,
 *          or succes flag set to false and a reason to why.
 */
NavPath Navigation_FindPath(Coordinates from, Coordinates to);

#endif