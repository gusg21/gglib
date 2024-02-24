#if !defined(GG_ASSETS_H)
#define GG_ASSETS_H

#include <stdlib.h>

#include "assets.h"
#include "scene.h"
#include "scripting.h"
#include "tiled.h"
#include "texture.h"

typedef enum gg_asset_type {
    ASSET_NONE,
    ASSET_TEXTURE,
    ASSET_TILED_MAP,
    ASSET_SCRIPT,
    ASSET_SCENE
} gg_asset_type_e;

typedef union gg_asset_data {
    gg_texture_t as_tex;
    gg_tiled_map_t as_tiled_map;
    gg_script_t as_script;
    gg_scene_t as_scene;
} gg_asset_data_u;

typedef struct gg_asset {
    gg_asset_type_e type;
    gg_asset_data_u data;
} gg_asset_t;

typedef struct gg_asset_pair gg_asset_pair_t;
struct gg_asset_pair {
    char* name;
    gg_asset_t asset;

    gg_asset_pair_t* next;
};

typedef struct gg_assets {
    gg_asset_pair_t* asset_list;
} gg_assets_t;

void Assets_Create(gg_assets_t* assets);
void Assets_LoadInternals(gg_assets_t* assets, gg_window_t* window, gg_state_t* state);
void Assets_Load(gg_assets_t* assets, gg_window_t* window, gg_state_t* state, gg_asset_type_e type, const char* name);
//gg_asset_t* Assets_Get(gg_assets_t* assets, const char* name);
bool Assets_Has(gg_assets_t* assets, const char* name);
bool Assets_Get(gg_assets_t* assets, gg_asset_t** asset_ptr, const char* name);
void Assets_Destroy(gg_assets_t* assets);

#endif // GG_ASSETS_H
