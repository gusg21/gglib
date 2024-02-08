#include "tileset.h"

void Tileset_CreateFromTexture(gg_tileset_t* tileset, gg_texture_t* texture, uint32_t tile_size, uint32_t tiles_wide) {
    tileset->texture = texture;
    tileset->tile_size = tile_size;
    tileset->tiles_wide = tiles_wide;
}

void Tileset_DrawTile(gg_tileset_t* tileset, gg_window_t* window, uint32_t x, uint32_t y, uint32_t tile_id) {
    Window_DrawSubTexture(window, tileset->texture, x, y, (tile_id % tileset->tiles_wide) * tileset->tile_size,
                          (tile_id / tileset->tiles_wide) * tileset->tile_size, tileset->tile_size, tileset->tile_size);
}