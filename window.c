#include "window.h"

// Contains platform-specific windowing functions
// Most of these map directly to Raylib and probably always will

void Window_CreateWindowed(gg_window_t* window, const char* title, uint32_t width, uint32_t height) {
    if (window->initialized) {
        CloseWindow();
    }

    InitWindow(width, height, title);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    window->width = width;
    window->height = height;
    window->initialized = IsWindowReady();
    window->fullscreen = false;  // TODO: Ensure that the window is windowed?

    SetTargetFPS(60);
}

void Window_CreateFullscreen(gg_window_t* window, const char* title) {
    if (window->initialized) {
        CloseWindow();
    }

    uint32_t width = GetScreenWidth();
    uint32_t height = GetScreenHeight();
    InitWindow(width, height, title);
    Window_SetFullscreen(window, true);

    SetTargetFPS(60);
}

void Window_SetFullscreen(gg_window_t* window, bool fullscreen) {
    if (IsWindowFullscreen() != fullscreen) {
        ToggleFullscreen();
    }

    window->fullscreen = fullscreen;
}

float Window_GetDeltaTime(gg_window_t* window) { return GetFrameTime(); }

bool Window_ShouldClose(gg_window_t* window) { return WindowShouldClose(); }

void Window_BeginDrawing(gg_window_t* window) { BeginDrawing(); }

void Window_BeginCameraDrawing(gg_window_t* window, gg_camera_t* camera) {
    BeginMode2D((Camera2D){
        .offset = (Vector2){camera->offset_x, camera->offset_y},
        .rotation = camera->rotation,
        .target = (Vector2){camera->x, camera->y},
        .zoom = camera->zoom,
    });
}

void Window_EndDrawing(gg_window_t* window) { EndDrawing(); }

void Window_EndCameraDrawing(gg_window_t* window, gg_camera_t* camera) { EndMode2D(); }

void Window_ClearScreen(gg_window_t* window, gg_color_t color) {
    ClearBackground((Color){.r = color.r, .g = color.g, .b = color.b, .a = color.a});
}

void Window_DrawTexture(gg_window_t* window, gg_texture_t* texture, uint32_t x, uint32_t y) {
    DrawTexture(texture->_handle, x, y, WHITE);
}

void Window_DrawSubTexture(gg_window_t* window, gg_texture_t* texture, uint32_t x, uint32_t y, uint32_t sx, uint32_t sy,
                           uint32_t sw, uint32_t sh) {
    DrawTextureRec(texture->_handle, (Rectangle){sx, sy, sw, sh}, (Vector2){x, y}, WHITE);
}

void Window_DrawDebugFPS(gg_window_t* window) { DrawFPS(10, 10); }