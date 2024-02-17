#include "ldefs.h"

#include "scene.h"
#include "window.h"

// SCENE FUNCTIONS
LDEF(Scene_GetWindow) {
    const gg_scene_t* scene = lua_topointer(L, 1);

    lua_pushlightuserdata(L, scene->window);

    return 1;
}

LDEF(Scene_GetCamera) {
    const gg_scene_t* scene = lua_topointer(L, 1);
    
    lua_pushlightuserdata(L, &scene->camera);
    
    return 1;
}

LDEF(Scene_GetActorByName) {
    const gg_scene_t* scene = lua_topointer(L, 1);

    const char* name = lua_tostring(L, 2);

    lua_pushlightuserdata(L, Scene_GetActorByName(scene, name));

    return 1;
}

// CAMERA FUNCTIONS
LDEF(Camera_SetPosition) {
    gg_camera_t* camera = lua_topointer(L, 1);

    int32_t x = lua_tonumber(L, 2);
    int32_t y = lua_tonumber(L, 3);

    camera->x = x;
    camera->y = y;

    return 0;
}

LDEF(Camera_SetZoom) {
    gg_camera_t* camera = lua_topointer(L, 1);

    float zoom = lua_tonumber(L, 2);

    camera->zoom = zoom;

    return 0;
}

// ACTOR FUNCTIONS
LDEF(Actor_GetPosition) {
    gg_actor_t* actor = lua_topointer(L, 1);

    lua_pushnumber(L, actor->transform.pos.x);
    lua_pushnumber(L, actor->transform.pos.y);

    return 2;
}

LDEF(Actor_SetPosition) {
    gg_actor_t* actor = lua_topointer(L, 1);

    int32_t x = lua_tointeger(L, 2);
    int32_t y = lua_tointeger(L, 3);

    actor->transform.pos.x = x;
    actor->transform.pos.y = y;

    return 0;
}

// WINDOW FUNCTIONS
LDEF(Window_DrawRectangle) {
    const gg_window_t* window = lua_topointer(L, 1);

    int32_t x = lua_tointeger(L, 2);
    int32_t y = lua_tointeger(L, 3);
    uint32_t w = lua_tointeger(L, 4);
    uint32_t h = lua_tointeger(L, 5);

    Window_DrawRectangle(window, x, y, w, h, COL(255, 128, 128));

    return 0;
}

void LDefs_LoadIntoScripting(gg_scripting_t* scripting) {
    LDEF_LOAD(scripting, Scene_GetWindow);
    LDEF_LOAD(scripting, Scene_GetCamera);
    LDEF_LOAD(scripting, Scene_GetActorByName);

    LDEF_LOAD(scripting, Camera_SetZoom);
    LDEF_LOAD(scripting, Camera_SetPosition);

    LDEF_LOAD(scripting, Actor_GetPosition);
    LDEF_LOAD(scripting, Actor_SetPosition);

    LDEF_LOAD(scripting, Window_DrawRectangle);
}
