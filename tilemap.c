#include "tilemap.h"

#include <stdlib.h>

void Tilemap_Create(gg_tilemap_t* tilemap, gg_tileset_t* tileset, uint32_t width, uint32_t height) {
    tilemap->tileset = tileset;
    tilemap->width = width;
    tilemap->height = height;
    tilemap->data = calloc(width * height, sizeof(uint32_t));
}

void Tilemap_Draw(gg_tilemap_t* tilemap, gg_window_t* window) {
    uint32_t tile_size = tilemap->tileset->tile_size;
    for (uint32_t xx = 0; xx < tilemap->width; xx++) {
        for (uint32_t yy = 0; yy < tilemap->height; yy++) {
            Tileset_DrawTile(tilemap->tileset, window, xx * tile_size, yy * tile_size,
                             tilemap->data[xx + yy * tilemap->width]);
        }
    }
}

void Tilemap_Destroy(gg_tilemap_t* tilemap) {}
