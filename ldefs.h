#if !defined(GG_LDEFS_H)
#define GG_LDEFS_H

#include "lua54/lua.h"
#include "scripting.h"

#define LDEF(name) static int LDEF_##name(lua_State* L)
#define LDEF_LOAD(scr, name) lua_register(scr->state, #name, LDEF_##name)

// SCENE FUNCTIONS
LDEF(Scene_GetWindow);

// WINDOW FUNCTIONS
LDEF(Window_DrawRectangle);

void LDefs_LoadIntoScripting(gg_scripting_t* scripting);

#endif  // GG_LDEFS_H
