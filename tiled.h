#if !defined(GG_TILED_H)
#define GG_TILED_H

#include "tilemap.h"
#include "tileset.h"
#include "texture.h"

typedef struct gg_tiled_map {
    gg_tilemap_t map;
    gg_tileset_t set;
    gg_texture_t tex;
} gg_tiled_map_t;

void TiledMap_LoadFromTMJ(gg_tiled_map_t* tmap, const char* path);
void TiledMap_Destroy(gg_tiled_map_t* tmap);

#endif // GG_TILED_H
