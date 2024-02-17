#include "ldefs.h"

#include "scene.h"
#include "window.h"

// SCENE FUNCTIONS
LDEF(Scene_GetWindow) {
    const gg_scene_t* scene = lua_topointer(L, 1);

    lua_pushlightuserdata(L, scene->window);

    return 1;
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

// TEXTURE FUNCTIONS
LDEF(Texture_LoadFromName) {

    return 0;
}

void LDefs_LoadIntoScripting(gg_scripting_t* scripting) {
    LDEF_LOAD(scripting, Scene_GetWindow);

    LDEF_LOAD(scripting, Window_DrawRectangle);
}
