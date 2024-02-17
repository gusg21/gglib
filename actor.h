#if !defined(GG_ACTOR_H)
#define GG_ACTOR_H

#include <stdbool.h>

#include "scripting.h"
#include "transform.h"

#define ACTOR_INVALID 0xFFFFFFFF
#define ACTOR_ROOT 0xFFFFFFFE

typedef struct gg_actor {      // TODO: actor.h?
    bool alive;                // Should we get updates? (NOTE: Don't modify directly!)
    bool visible;              // Should we get drawn?
    gg_transform_t transform;  // Our local transform
    uint32_t parent_id;        // The ID within the scene of our parent
    uint32_t script_handle;    // The handle to our table of data 'n' functions
} gg_actor_t;

void Actor_ResetActor(gg_actor_t* actor);
void Actor_CallScriptFunction(gg_actor_t* actor, gg_scripting_t* scripting, const char* func_name);
void Actor_CallScriptFunctionWithPointer(gg_actor_t* actor, gg_scripting_t* scripting, const char* func_name,
                                         void* pointer);

#endif  // GG_ACTOR_H
