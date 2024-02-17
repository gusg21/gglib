#include "scripting.h"

#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "lua54/lauxlib.h"
#include "lua54/lualib.h"
#include "ldefs.h"

void Scripting_Initialize(gg_scripting_t* script) {
    script->next_handle = 1;

    script->state = luaL_newstate();
    luaL_openlibs(script->state);
    LDefs_LoadIntoScripting(script);
}

uint32_t Scripting_LoadScript(gg_scripting_t* script, const char* data) {
    // printf("Loading script %s\n", data);

    char handle_string[16] = {0};
    uint32_t handle = script->next_handle++;
    sprintf(handle_string, SCRIPTING_HANDLE_FORMAT, handle);

    if (luaL_dostring(script->state, data) != LUA_OK) {
        printf("ERROR (loading): %s", lua_tostring(script->state, -1));
    }
    lua_setglobal(script->state, handle_string);

    lua_settop(script->state, 0);  // Empty the stack

    return handle;
}

void Scripting_Call(gg_scripting_t* script, const char* func_name, uint32_t handle) {
    char handle_string[16] = {0};
    sprintf(handle_string, SCRIPTING_HANDLE_FORMAT, handle);

    lua_getglobal(script->state, handle_string);  // [table]
    lua_getfield(script->state, -1, func_name);   // [table] [function]
    if (!lua_isnil(script->state, -1)) {
        lua_pushvalue(script->state, -2);                   // [table] [function] [table]
        if (lua_pcall(script->state, 1, 0, 0) != LUA_OK) {  // [table]
            char* err_text = Log_TextFormat("ERROR (func %s): %s", func_name, lua_tostring(script->state, -1));
            Log_Err(err_text);
            free(err_text);
        }
    } else {
        // printf("nil func_name %s\n", func_name);
    }
    lua_settop(script->state, 0);  // Empty the stack
}

void Scripting_CallWithPointer(gg_scripting_t* script, const char* func_name, uint32_t handle, void* pointer) {
    char handle_string[16] = {0};
    sprintf(handle_string, SCRIPTING_HANDLE_FORMAT, handle);

    lua_getglobal(script->state, handle_string);  // [table]
    lua_getfield(script->state, -1, func_name);   // [table] [function]
    if (!lua_isnil(script->state, -1)) {
        lua_pushvalue(script->state, -2);                   // [table] [function] [table]
        lua_pushlightuserdata(script->state, pointer);      // [table] [function] [table] [ptr]
        if (lua_pcall(script->state, 2, 0, 0) != LUA_OK) {  // [table]
            char* err_text = Log_TextFormat("ERROR (func %s): %s", func_name, lua_tostring(script->state, -1));
            Log_Err(err_text);
            free(err_text);
        }
    } else {
        // printf("nil func_name %s\n", func_name);
    }
    lua_settop(script->state, 0);  // Empty the stack
}