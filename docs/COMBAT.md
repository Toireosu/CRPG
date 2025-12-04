# COMBAT

## Structure
* Init 
    * Player init combat -> from btn
    * Enemy init combat -> from range and (e.perception - p.sneak)
    * Stop all current entity action
* Roll initiative
    * Higher if initiated combat
    * Calculated from (perception)
* Turns
    * Creature has x AP
    * Creature can do actions that cost AP until
        * Out of AP
        * End turn
* Actions
    * Using items
    * Moving
    * Attacking (weapons, fists)
* Battle ends when 
    * Player dead
    * Enemy dead
    * Player flee
    * Enemy flee

## Code

* combat
    * init()
    * start_combat(Entity*)
    * try_end_combat()
    * is_combat()
    * begin_turn(Entity*)
    * should_take_turn(Entity*)
    * end_turn(Entity*)
* character_controller
    * Listen to is_combat, should_take_turn and end_turn
* ai_character_controller
    * Listen to is_combat, should_take_turn and end_turn

