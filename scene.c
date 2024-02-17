#include "scene.h"

#include <stdio.h>
#include <string.h>

void Scene_Create(gg_scene_t* scene, gg_window_t* window) {
    memset(scene->actors, 0, SCENE_MAX_ACTORS * sizeof(gg_actor_t));
    scene->actors_alive = 0;

    scene->window = window;

    Camera_Create(&scene->camera, Window_GetWidth(window), Window_GetHeight(window), 0, 0);

    Scripting_Initialize(&scene->scripting);
}

uint32_t Scene_GetNewAndActivate(gg_scene_t* scene, gg_script_t* script) {
    // TODO: Make this function take in the window too? Instead of attaching it to the scene?

    for (uint32_t actor_id = 0; actor_id < SCENE_MAX_ACTORS; actor_id++) {
        gg_actor_t* actor = &scene->actors[actor_id];

        if (!actor->alive) {
            Actor_ResetActor(actor);

            actor->parent_id = ACTOR_ROOT;
            actor->actor_id = actor_id;
            actor->alive = true;
            actor->visible = true;

            scene->actors_alive++;

            if (script != NULL) {
                actor->script_handle = Scripting_LoadScript(&scene->scripting, script);
                Actor_CallScriptFunctionWithTwoPointers(actor, &scene->scripting, "initialize", scene, actor);
            }

            return actor_id;
        }
    }

    return ACTOR_INVALID;
}

void Scene_CreateObjectsFromTiledMap(gg_scene_t* scene, gg_assets_t* assets, gg_tiled_map_t* tmap) {
    if (tmap == NULL) {
        printf("ERROR: Invalid tiled map");
        return;
    }

    gg_tiled_object_t* object = tmap->objs;
    while (object != NULL) {
        gg_script_t* script = NULL;
        if (object->script_name != NULL) {
            gg_asset_t* asset;
            bool valid = Assets_Get(assets, &asset, object->script_name);
            if (valid) {
                script = &asset->data.as_script;
            }
        }

        uint32_t id = Scene_GetNewAndActivate(scene, script);
        gg_actor_t* actor = Scene_GetActorByID(scene, id);

        actor->transform.pos.x = object->x;
        actor->transform.pos.y = object->y;

        actor->name = malloc(sizeof(char) * 64);
        TextCopy(actor->name, object->name);

        object = object->next;
    }
}

gg_actor_t* Scene_GetActorByID(gg_scene_t* scene, uint32_t id) { 
    for (size_t i = 0; i < SCENE_MAX_ACTORS; i++) {
        gg_actor_t* actor = &scene->actors[i];
        if (actor->actor_id == id) {
            return actor;
        }
    }
    return NULL;
}

gg_actor_t* Scene_GetActorByName(gg_scene_t* scene, const char* name) { 
    for (int i = 0; i < SCENE_MAX_ACTORS; i++) {
        gg_actor_t* actor = &scene->actors[i];
        if (TextIsEqual(actor->name, name)) {
            return actor;
        }
    }
    return NULL;
 }

 void Scene_Ready(gg_scene_t* scene) {
    for (int i = 0; i < SCENE_MAX_ACTORS; i++) {
         gg_actor_t* actor = &scene->actors[i];
         if (actor->alive) {
             Actor_CallScriptFunction(actor, &scene->scripting, "ready");
         }
     }
 }

 void Scene_Update(gg_scene_t* scene, float delta) {
     for (int i = 0; i < SCENE_MAX_ACTORS; i++) {
         gg_actor_t* actor = &scene->actors[i];
         if (actor->alive) {
             Actor_CallScriptFunction(actor, &scene->scripting, "update");
         }
     }
}

void Scene_Draw(gg_scene_t* scene, gg_window_t* window) {
    for (int i = 0; i < SCENE_MAX_ACTORS; i++) {
        gg_actor_t* actor = &scene->actors[i];
        if (actor->visible) {
            Actor_CallScriptFunction(actor, &scene->scripting, "draw");
        }
    }
}
