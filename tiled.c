#include "tiled.h"

#include <string.h>

#include "external/cute_tiled.h"

void TiledMap_LoadFromTMJ(gg_tiled_map_t* tmap, const char* path) {
    cute_tiled_map_t* map = cute_tiled_load_map_from_file(path, NULL);
    cute_tiled_layer_t* layer = &map->layers[0];
    cute_tiled_tileset_t* tileset = &map->tilesets[0];

    if (strcmp(layer->type.ptr, "tilelayer") == 0) {
        // Load texture
        const char* full_path = TextFormat("%s/%s", GetDirectoryPath(path), tileset->image.ptr);
        Texture_GetRaw(&tmap->tex, full_path);
        
        // Load tileset
        Tileset_CreateFromTexture(&tmap->set, &tmap->tex, tileset->tilewidth, tileset->columns);

        // Load tilemap
        Tilemap_Create(&tmap->map, &tmap->set, map->width, map->height);

        // Copy in tile data
        memcpy(tmap->map.data, layer->data, layer->width * layer->height * sizeof(uint32_t));
    } else {
        // TODO: Error!
    }

    cute_tiled_free_map(map);
}

void TiledMap_Destroy(gg_tiled_map_t* tmap) {
    Tilemap_Destroy(&tmap->map);
    Tileset_Destroy(&tmap->set);
    // NOTE: No "Texture_Destroy()" because textures are assumed to be lightweight pointers
    // to full textures allocated elsewhere.
}
