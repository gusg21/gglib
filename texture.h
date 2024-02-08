#if !defined(TEXTURE_H)
#define TEXTURE_H

#include <raylib.h>

typedef struct gg_texture {
    Texture2D _handle;  // Platform-specific
} gg_texture_t;

void Texture_Get(gg_texture_t* texture, const char* name);

#endif  // TEXTURE_H
