#ifndef GAME_H
#define GAME_H

#include "scene.h"

typedef struct Game {
    Scene* scene;
} Game;

void Game_Init(Game* game);

#endif