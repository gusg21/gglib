#include "texture.h"

#include <stdio.h>

void Texture_Get(gg_texture_t* texture, const char* name) {
    char formatted_path[256] = {0};  // TODO: fixed buffer size :3
    sprintf(formatted_path, "assets/%s.png", name);

    texture->_handle = LoadTexture(formatted_path);
}
