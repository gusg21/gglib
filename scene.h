#if !defined(GG_SCENE_H)
#define GG_SCENE_H

#define SCENE_MAX_ACTORS 1024

#include <stdint.h>

#include "actor.h"
#include "assets.h"
#include "scripting.h"
#include "transform.h"
#include "window.h"

typedef struct gg_scene {
    // TODO: please don't let this struct get bloated :(

    gg_actor_t actors[SCENE_MAX_ACTORS];
    uint32_t actors_alive;

    gg_camera_t camera;
    gg_assets_t assets;
    gg_scripting_t scripting;

    gg_window_t* window;  // NOTE: Not managed by the scene, but the scripting needs it to do useful stuff. How fix?
} gg_scene_t;

void Scene_Create(gg_scene_t* scene, gg_window_t* window);
uint32_t Scene_GetNewAndActivate(gg_scene_t* scene, gg_script_t* script);
void Scene_CreateObjectsFromTiledMap(gg_scene_t* scene, gg_assets_t* assets, gg_tiled_map_t* tmap);
gg_actor_t* Scene_GetActorByID(gg_scene_t* scene, uint32_t id);
gg_actor_t* Scene_GetActorByName(gg_scene_t* scene, const char* name);
void Scene_Ready(gg_scene_t* scene);
void Scene_Update(gg_scene_t* scene, float delta);
void Scene_Draw(gg_scene_t* scene, gg_window_t* window);

#endif  // GG_SCENE_H
