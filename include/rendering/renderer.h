#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "data/game.h"

extern Texture floor_texture;
extern Texture wall_texture;
extern Texture character_texture;
extern Texture roof_texture;

typedef struct Sprite {
    Texture texture;
    Rectangle source;
    Vector2 position;
    Vector2 size;
    Vector2 origin;
    int z;
} Sprite;

void Renderer_Init();
void Renderer_AddSprite(Sprite sprite);
void Renderer_Render(Game* game);
int Renderer_CalculateZ(Vector2 coordinate);
// render_ui.c
void Renderer_RenderUI(Game* game);
// render_map.c
void Renderer_CollectMapSprites(const Map* map);
void Renderer_RenderMapBackground(const Map* map);
void Renderer_RenderMapForeground(const Scene* scene);
void Renderer_MapInit(const Map* map);
// render_entity.c
void Renderer_CollectEntitySprites(const Scene* scene);

#endif