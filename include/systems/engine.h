#ifndef ENGINE_H
#define ENGINE_H

#include "data/scene.h"

void Engine_Init();
void Engine_LoadScene(int id);
void Engine_Run();

Scene* Engine_GetScene();

#endif 