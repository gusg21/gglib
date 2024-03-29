#include "assets.h"
#include "log.h"

#include <raylib.h>
#include <stdio.h>

void Assets_Create(gg_assets_t* assets) {
    assets->asset_list = NULL;
}

void Assets_LoadInternals(gg_assets_t* assets, gg_window_t* window, gg_state_t* state) {
    Assets_Load(assets, window, state, ASSET_SCRIPT, "gg/map");
}

void Assets_Load(gg_assets_t* assets, gg_window_t* window, gg_state_t* state, gg_asset_type_e type, const char* name) {
    gg_asset_pair_t* pair = malloc(sizeof(gg_asset_pair_t));

    pair->name = calloc(256, sizeof(char));
    TextCopy(pair->name, name);
    pair->asset.type = type;

    // Load actual data
    char formatted_path[256] = {0};
    switch (type) {
        case ASSET_TEXTURE:
            sprintf(formatted_path, "assets/%s.png", name);
            Texture_LoadFromFile(&pair->asset.data.as_tex, formatted_path);
            break;
        case ASSET_TILED_MAP:
            sprintf(formatted_path, "assets/%s.tmj", name);
            TiledMap_LoadFromTMJ(&pair->asset.data.as_tiled_map, formatted_path);
            break;
        case ASSET_SCRIPT:
            sprintf(formatted_path, "assets/%s.lua", name);
            Script_LoadFromLua(&pair->asset.data.as_script, formatted_path);
            break;
        case ASSET_SCENE:
            // This asset is FANCY (read: painful) and needs the asset manager itself!!!
            // Yippee!!!
            sprintf(formatted_path, "assets/%s.json", name);
            Scene_LoadFromJson(&pair->asset.data.as_scene, assets, window, state, formatted_path);
            break;
        default:
            printf("Unsupported asset type %d...\n", type);
            break;
    }

    // Easy out if first pair
    if (assets->asset_list == NULL) {
        assets->asset_list = pair;
        return;
    }

    // Append to linked list
    // TODO: Might be broken???? I was working on it when it broke (2/16/24) and
    // it started working suddenly. not sure what's up, good luck soldier
    gg_asset_pair_t* last_pair = assets->asset_list;
    while (last_pair->next != NULL) {
        last_pair = last_pair->next;
    }
    last_pair->next = pair;
}

// gg_asset_t* Assets_Get(gg_assets_t* assets, const char* name) {
//     gg_assets_t* asset = NULL;
//     Assets_SafeGet(assets, &asset, name);
//     return asset;
// }

bool Assets_Has(gg_assets_t* assets, const char* name) { 
    gg_asset_pair_t* pair = assets->asset_list;

    if (pair == NULL) return false;

    while (pair != NULL) {
        if (TextIsEqual(pair->name, name)) {
            return true;
        }

        pair = pair->next;
    }

    Log_Warn(Log_TextFormat("ASSETS: Unable to HAS() asset name %s!", name));
    return false;
}

bool Assets_Get(gg_assets_t* assets, gg_asset_t** asset_ptr, const char* name) {
    gg_asset_pair_t* pair = assets->asset_list;

    if (pair == NULL) return false;

    while (pair != NULL) {
        if (TextIsEqual(pair->name, name)) {
            (*asset_ptr) = &pair->asset;
            return true;
        }

        pair = pair->next;
    }

    Log_Warn(Log_TextFormat("ASSETS: Unable to GET() asset name %s!", name));
    return false;
}

void Assets_Destroy(gg_assets_t* assets) {
    // TODO: Cleanup
}