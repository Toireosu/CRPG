#ifndef COMBAT_H
#define COMBAT_H

#include "data/entity.h"

void Combat_Init();
void Combat_Start(Scene* scene, Entity* instigator);
void Combat_TryEnd();
void Combat_IsCombat();

bool Combat_BeginTurn(Entity* entity);
bool Combat_ShouldTakeTurn(Entity* entity);
bool Combat_EndTurn(Entity* entity);

#endif