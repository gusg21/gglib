#if !defined(TILESET_H)
#define TILESET_H

#include <stdint.h>

#include "texture.h"
#include "window.h"

typedef struct gg_tileset {
    gg_texture_t* texture;
    uint32_t tile_size;
    uint32_t tiles_wide;
} gg_tileset_t;

void Tileset_CreateFromTexture(gg_tileset_t* tileset, gg_texture_t* texture, uint32_t tile_size, uint32_t tiles_wide);
void Tileset_DrawTile(gg_tileset_t* tileset, gg_window_t* window, uint32_t x, uint32_t y, uint32_t tile_id);

#endif  // TILESET_H
