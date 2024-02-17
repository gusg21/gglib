#include "actor.h"

#include "scripting.h"

void Actor_ResetActor(gg_actor_t* actor) {
    actor->transform = (gg_transform_t){
        .pos = V2ZERO(),
        .rot = 0.f,
        .scale = V2ONE(),
    };
    actor->parent_id = ACTOR_ROOT;
    actor->alive = false;
    actor->visible = false;
};

void Actor_CallScriptFunction(gg_actor_t* actor, gg_scripting_t* scripting, const char* func_name) {
    if (actor->script_handle != SCRIPTING_BAD_HANDLE) {
        Scripting_Call(scripting, func_name, actor->script_handle);
    }
}

void Actor_CallScriptFunctionWithPointer(gg_actor_t* actor, gg_scripting_t* scripting, const char* func_name,
                                         void* pointer) {
    if (actor->script_handle != SCRIPTING_BAD_HANDLE) {
        Scripting_CallWithPointer(scripting, func_name, actor->script_handle, pointer);
    }
}
