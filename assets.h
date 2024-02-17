#if !defined(GG_ASSETS_H)
#define GG_ASSETS_H

#include <stdlib.h>

#include "tiled.h"
#include "texture.h"

typedef enum gg_asset_type {
    ASSET_NONE,
    ASSET_TEXTURE,
    ASSET_TILED_MAP
} gg_asset_type_e;

typedef union gg_asset_data {
    gg_texture_t as_tex;
    gg_tiled_map_t as_tiled_map;
} gg_asset_data_u;

typedef struct gg_asset {
    gg_asset_type_e type;
    gg_asset_data_u data;
} gg_asset_t;

typedef struct gg_asset_pair gg_asset_pair_t;
struct gg_asset_pair {
    const char* name;
    gg_asset_t asset;

    gg_asset_pair_t* next;
};

typedef struct gg_assets {
    gg_asset_pair_t* asset_list;
} gg_assets_t;

void Assets_Create(gg_assets_t* assets);
void Assets_Load(gg_assets_t* assets, gg_asset_type_e type, const char* name);
gg_asset_t* Assets_Get(gg_assets_t* assets, const char* name);
void Assets_Destroy(gg_assets_t* assets);

#endif // GG_ASSETS_H
