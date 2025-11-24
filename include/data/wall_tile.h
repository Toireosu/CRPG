#ifndef WALL_TILE_H
#define WALL_TILE_H

#define WALL_TILE_NUM_WALLS 4

#define WALL_TILE_EMPTY (WallTile) { 0, 0, 0, 0 }

typedef struct WallTile {
    char ids[WALL_TILE_NUM_WALLS];
} WallTile;

void WallTile_Init(WallTile* tile);

#endif 