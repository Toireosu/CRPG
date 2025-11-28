#ifndef WALL_TILE_H
#define WALL_TILE_H

#define WALL_TILE_NUM_WALLS 4

#define WALL_TILE_EMPTY (WallTile) { 0, 0, 0, 0 }


/** 
 * @struct WallTile
 * 
 * @brief A struct that holds the ids for all 4 possible walls of a tile.
 */
typedef struct WallTile {
    char ids[WALL_TILE_NUM_WALLS];
} WallTile;

/**
 * @brief Initializes all ids of a WallTile to 0 (empty).
 * 
 * @param tile The WallTile struct to be initialized.
 * @note Unused (??)
 */
void WallTile_Init(WallTile* tile);

#endif 