#if !defined(GG_SCRIPTING_H)
#define GG_SCRIPTING_H

#include <stdint.h>
#include <stdbool.h>

#include "lua54/lua.h"

#define SCRIPTING_HANDLE_FORMAT "hnd__%d"
#define SCRIPTING_BAD_HANDLE 0

#define SCRIPT_MAX_LENGTH 4096

typedef struct gg_scripting {
    lua_State* state;
    uint32_t next_handle;
} gg_scripting_t;

typedef struct gg_script {
    char* text;
    bool ok;
} gg_script_t;

void Script_LoadFromLua(gg_script_t* code, const char* path);

void Scripting_Initialize(gg_scripting_t* script);
uint32_t Scripting_LoadScript(gg_scripting_t* script, gg_script_t* code);
// TODO: Get object handle
void Scripting_Call(gg_scripting_t* script, const char* func_name, uint32_t handle);
void Scripting_CallWithFloat(gg_scripting_t* script, const char* func_name, uint32_t handle, float f);
void Scripting_CallWithPointer(gg_scripting_t* script, const char* func_name, uint32_t handle, void* pointer);
void Scripting_CallWithTwoPointers(gg_scripting_t* script, const char* func_name, uint32_t handle, void* pointer1,
                                   void* pointer2);

#endif  // GG_SCRIPTING_H
