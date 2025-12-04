#include "systems/combat.h"

#include "kvec.h"
#include <stdlib.h>
#include <stdbool.h>
#include "data/scene.h"

#define COMBAT_RADIUS 20

typedef struct {
    int roll; 
    Entity* entity;
} EntityInitiative;

static struct {
    kvec_t(EntityInitiative) initiative;
    bool is_combat;
    int turn_index;
    Entity* instigator;
} combat;

void Combat_Init() {
    kv_init(combat.initiative);
    combat.is_combat = false;
    combat.turn_index = 0;
    combat.instigator = NULL;
}

static bool Combat_IsInstigator(Entity* entity) {
    return entity == combat.instigator;
} 

static inline int  Combat_CompareInitiative(void* a, void* b) {
    EntityInitiative pa = *(EntityInitiative*)a;
    EntityInitiative pb = *(EntityInitiative*)b;
    if (pa.roll > pb.roll) return -1;
    if (pa.roll < pb.roll) return 1;
    return 0;
}

static EntityInitiative Combat_RollInitiative(Entity* entity) {
    int instigator_bonus = Combat_IsInstigator(entity) ? 2 : 0;
    int roll = rand() % 5;
    
    return (EntityInitiative) {
        .roll = roll + instigator_bonus,
        .entity = entity,
    };
}

static void Combat_CollectInitiative(Scene* scene) {

    EntityVector entities_in_range = Scene_GetEntitiesArea(scene, combat.instigator->position, COMBAT_RADIUS);

    for (int i = 0; i < kv_size(entities_in_range); i++)
        kv_push(EntityInitiative, combat.initiative, Combat_RollInitiative(kv_A(entities_in_range, i)));

    kv_destroy(entities_in_range);

    // Sort on initiative
    qsort(combat.initiative.a, kv_size(combat.initiative), sizeof(EntityInitiative), Combat_CompareInitiative);
}   

void Combat_Start(Scene* scene, Entity* instigator) {
    if (combat.is_combat) return;
    if (instigator == NULL) return;

    combat.instigator = instigator;
    combat.is_combat = true;
    combat.turn_index = 0;
    kv_size(combat.initiative) = 0;

    Combat_CollectInitiative(scene);
}

void Combat_TryEnd() {
    combat.instigator = NULL;
    combat.is_combat = false;
    kv_destroy(combat.initiative);
}

void Combat_IsCombat() { return combat.is_combat; }

bool Combat_BeginTurn(Entity* entity) {
    return true; 
}

bool Combat_ShouldTakeTurn(Entity* entity) {
    return entity == kv_A(combat.initiative, combat.turn_index).entity;
}

bool Combat_EndTurn(Entity* entity) {
    if (!Combat_ShouldTakeTurn(entity)) return false;

    combat.turn_index % kv_size(combat.initiative);
    return true;
}