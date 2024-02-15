#if !defined(TEXTURE_H)
#define TEXTURE_H

#include <raylib.h> // Platform specific
#include <stdint.h>

typedef struct gg_texture {
    Texture2D _handle;  // Platform-specific
} gg_texture_t;

void Texture_Get(gg_texture_t* texture, const char* name);
void Texture_GetRaw(gg_texture_t* texture, const char* path);
uint32_t Texture_GetWidth(gg_texture_t* texture);
uint32_t Texture_GetHeight(gg_texture_t* texture);

#endif  // TEXTURE_H
