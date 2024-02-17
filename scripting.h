#if !defined(GG_SCRIPTING_H)
#define GG_SCRIPTING_H

#include <stdint.h>
#include "lua54/lua.h"

#define SCRIPTING_HANDLE_FORMAT "hnd__%d"
#define SCRIPTING_BAD_HANDLE 0

typedef struct gg_scripting {
    lua_State* state;
    uint32_t next_handle;
} gg_scripting_t;

void Scripting_Initialize(gg_scripting_t* script);
uint32_t Scripting_LoadScript(gg_scripting_t* script, const char* data);
// TODO: Get object handle
void Scripting_Call(gg_scripting_t* script, const char* func_name, uint32_t handle);
void Scripting_CallWithPointer(gg_scripting_t* script, const char* func_name, uint32_t handle, void* pointer);

#endif  // GG_SCRIPTING_H
