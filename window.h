#if !defined(GG_WINDOW_H)
#define GG_WINDOW_H

#include <stdbool.h>
#include <stdint.h>

#include "color.h"
#include "texture.h"
#include "camera.h"

typedef struct gg_window {
    bool initialized;
    bool fullscreen;
    uint32_t width, height;
} gg_window_t;

void Window_CreateWindowed(gg_window_t* window, const char* title, uint32_t width, uint32_t height);
void Window_CreateFullscreen(gg_window_t* window, const char* title);
void Window_SetFullscreen(gg_window_t* window, bool fullscreen);
uint32_t Window_GetWidth(gg_window_t* window);
uint32_t Window_GetHeight(gg_window_t* window);
float Window_GetDeltaTime(gg_window_t* window);
bool Window_ShouldClose(gg_window_t* window);
void Window_BeginDrawing(gg_window_t* window);
void Window_BeginCameraDrawing(gg_window_t* window, gg_camera_t* camera);
void Window_EndDrawing(gg_window_t* window);
void Window_EndCameraDrawing(gg_window_t* window, gg_camera_t* camera);
void Window_ClearScreen(gg_window_t* window, gg_color_t color);
void Window_DrawTexture(gg_window_t* window, gg_texture_t* texture, uint32_t x, uint32_t y);
void Window_DrawSubTexture(gg_window_t* window, gg_texture_t* texture, uint32_t x, uint32_t y, uint32_t sx, uint32_t sy,
                           uint32_t sw, uint32_t sh);
void Window_DrawDebugFPS(gg_window_t* window);

#endif  // GG_WINDOW_H
