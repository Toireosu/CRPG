## Stats
    * HP
    * Attributes (TBA)
    * Restoration rate
    * Armor
    * AP
    * Levelable skills
    * Background 
    * Sub-struct: CombatStats (used for critters?)

## Inventory
    * Item view
    * Drop, use (on certain items), Inspect
    * hasItem()
    * Amount of slots defined by your strength and any slot boosting items.
    * Can set item as main hand or off hand items etc.
    * Hooverable descriptions of items.
    * Dragable

## Items
    * Weapons.
    * Currency.
    * Consumables.
    * Stat boosting.
    * Quest items.

## Entity
    * Position
    * Renderer
    * Inspectable
    * Type { Character, Critter, Object }
    * data { Character { Stats, Appearance, }, Critter { Stats, Type }, Object { Type, Interaction }}
    * Inventory* 
    * Dialogue*
    * most of these should have optional scripting nodes (e.g. a switch that triggers something else in the scene)

## Map
    Layered
    * Farground -> things that are behind the floor
    * Background -> the floor | nothing
    * Midground -> doors, walls, entities, we must take into account screen coordinates for render order here
    * Fog of war ?
    * Foreground -> roofs and such  

## Game controller
    Should know which parts of the game are interactable at which points
    * Probably some kind of interaction tree? 
    * Knows when combat is started and when we can exit.

## Player UI
    * Knows which buttons can be used when
    * Shows HP 
    * Shows equiped weapons
    * Shows buttons
    * Shows pause button
    * Shows event notifications
    * Shows current character when in battle
    * Open inventory (only on player)
    * End turn

## Pause menu
    * Continue
    * Save
    * Load
    * Settings
    * Exit
    * Pauses game (regardeless of Combat state)

## Mouse manager
    * Check hover and clicks in hierarcy.

## Camera
    * Can scroll to map bounds.
    * Reacts to mouse -- when not showing pause menu or inventory etc...

## Window system 
    * Render to render texture for post-process
    * 3:4 or 16:9

## Random System
    * List of random values, saved state in file. Make sure that the random number will be the same even when trying to save scum. 

## Save/Load System