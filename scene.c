#include "scene.h"

#include <string.h>

void Scene_Create(gg_scene_t* scene, gg_window_t* window) {
    memset(scene->actors, 0, SCENE_MAX_ACTORS * sizeof(gg_actor_t));
    scene->actors_alive = 0;

    scene->window = window;

    Scripting_Initialize(&scene->scripting);
}

uint32_t Scene_GetNewAndActivate(gg_scene_t* scene, const char* script) {
    // TODO: Make this function take in the window too? Instead of attaching it to the scene?

    for (uint32_t actor_id = 0; actor_id < SCENE_MAX_ACTORS; actor_id++) {
        gg_actor_t* actor = &scene->actors[actor_id];

        if (!actor->alive) {
            Actor_ResetActor(actor);
            actor->alive = true;
            actor->visible = true;

            scene->actors_alive++;

            if (script != NULL) {
                actor->script_handle = Scripting_LoadScript(&scene->scripting, script);
                Actor_CallScriptFunctionWithPointer(actor, &scene->scripting, "initialize", scene);
            }

            return actor_id;
        }
    }

    return ACTOR_INVALID;
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
