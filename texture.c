#include "texture.h"

#include <stdint.h>
#include <stdio.h>

void Texture_Get(gg_texture_t* texture, const char* name) {
    char formatted_path[256] = {0};  // TODO: fixed buffer size :3
    sprintf(formatted_path, "assets/%s.png", name);

    Texture_GetRaw(texture, formatted_path);
}

void Texture_GetRaw(gg_texture_t* texture, const char* path) { texture->_handle = LoadTexture(path); }

uint32_t Texture_GetWidth(gg_texture_t* texture) { return texture->_handle.width; }

uint32_t Texture_GetHeight(gg_texture_t* texture) { return texture->_handle.height; }
