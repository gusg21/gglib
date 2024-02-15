#if !defined(GG_SCENE_H)
#define GG_SCENE_H

#define SCENE_MAX_ACTORS 1024

#include <stdint.h>

#include "transform.h"
#include "window.h"

typedef struct gg_actor {  // TODO: actor.h?
    bool alive;            // Should we get updates?
    bool visible;          // Should we get drawn?
    uint32_t parent_id;
    gg_transform_t transform;
} gg_actor_t;

typedef struct gg_scene {
    gg_actor_t actors[SCENE_MAX_ACTORS];
} gg_scene_t;

void Scene_Create(gg_scene_t* scene);
void Scene_Update(gg_scene_t* scene, float delta);
void Scene_Draw(gg_scene_t* scene, gg_window_t* window);

#endif  // GG_SCENE_H
