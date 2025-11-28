#include "data/wall_tile.h"

const WallTile WALL_TILE_EMPTY = {{ 0, 0, 0, 0 }};

void WallTile_Init(WallTile* tile) {
    for (int i = 0; i < WALL_TILE_NUM_WALLS; i++) {
        tile->ids[i] = 0;
    }
}