#include "data/wall_tile.h"

void WallTile_Init(WallTile* tile) {
    for (int i = 0; i < WALL_TILE_NUM_WALLS; i++) {
        tile->ids[i] = 0;
    }
}