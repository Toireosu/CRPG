#ifndef GAME_H
#define GAME_H

#include "scene.h"
#include "event_log.h"

typedef struct Game {
    Scene* scene;
} Game;

void Game_Init(Game* game);

#endif