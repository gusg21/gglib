#include "scene.h"

#include <string.h>

void Scene_Create(gg_scene_t* scene) {
    memset(scene->actors, 0, SCENE_MAX_ACTORS * sizeof(gg_actor_t));
}

void Scene_Update(gg_scene_t* scene, float delta) {

}

void Scene_Draw(gg_scene_t* scene, gg_window_t* window) {
    for (int i = 0; i < SCENE_MAX_ACTORS; i++) {
        gg_actor_t* actor = &scene->actors[i];
        if (actor->alive) {
            Window_DrawRectangle();
        }
    }
}
