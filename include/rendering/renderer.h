#ifndef RENDERER_H
#define RENDERER_H

#include "data/scene.h"
#include "raylib.h"

extern Texture floor_texture;
extern Texture wall_texture;
extern Texture character_texture;
extern Texture roof_texture;

/**
 * @brief A struct containing all data needed for displaying a 
 *          sprite from a texture atlas at a certain position.
 * @todo move to data?
 */
typedef struct Sprite {
    Texture texture;
    Rectangle source;
    Vector2 position;
    Vector2 size;
    Vector2 origin;
    int z;
} Sprite;

/**
 * @brief Initializes the renderer.
 */
void Renderer_Init();

/**
 * @brief Adds given sprite to the z-sorted render stack.
 * @param sprite The Sprite struct to be added. 
 */
void Renderer_AddSprite(Sprite sprite);

/**
 * @brief Renders the game based on current state.
 */
void Renderer_Render();

/**
 * @brief Helper function for calculating Z-index based on positional coordinates.
 * 
 * @param coords The (x, y) coordinates to generate Z from.
 * @return The calculated Z-index.
 */ 
int Renderer_CalculateZ(Vector2 coords);

//------------------- render_ui.c --------------------------------

/**
 * @brief Renders game ui based on current state.
 */
void Renderer_RenderUI();

//------------------ render_map.c ---------------------------------

/**
 * @brief Collects all z-order sprites from the map.
 * 
 * @param map The map from which to collect the sprites.
 */
void Renderer_CollectMapSprites(const Map* map);

/** 
 * @brief Renders the background of the given map.
 * 
 * @param map The map which background should be rendered.
 */
void Renderer_RenderMapBackground(const Map* map);

/**
 * @brief Renders the foreground of the given map.
 * 
 * @param map The map which foreground should be rendered.
 */
void Renderer_RenderMapForeground(const Scene* scene);

/**
 * @brief Initializes the give map for rendering.
 * @note Should be called upon switching map.
 */
void Renderer_MapInit(const Map* map);

//------------------- render_entity.c ----------------------------

/**
 * @brief Collects the z-order entity sprites from given scene.
 * 
 * @param scene The scene context to collect entities from. 
 */
void Renderer_CollectEntitySprites(const Scene* scene);

#endif