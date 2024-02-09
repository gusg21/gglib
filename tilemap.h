#if !defined(GG_TILEMAP_H)
#define GG_TILEMAP_H

#include "tileset.h"

typedef struct gg_tilemap {
    gg_tileset_t* tileset;

    uint32_t* data;
    uint32_t width;
    uint32_t height;
} gg_tilemap_t;

void Tilemap_Create(gg_tilemap_t* tilemap, gg_tileset_t* tileset, uint32_t width, uint32_t height);
void Tilemap_Draw(gg_tilemap_t* tilemap, gg_window_t* window);
void Tilemap_Destroy(gg_tilemap_t* tilemap);

#endif // GG_TILEMAP_H
