#include "external/cimgui_impl_raylib.h"

#include "state.h"
#include "assets.h"
#include "color.h"
#include "log.h"
#include "scene.h"
#include "tiled.h"

void State_Init(gg_state_t* state) {
    ImGui_ImplRaylib_Init();

    Keys_Create(&state->keys);
    state->current_scene = NULL;
}

void State_SetCurrentScene(gg_state_t* state, gg_scene_t* scene) { state->current_scene = scene; }

void State_DoLoop(gg_state_t* state, gg_window_t* window) {
    if (state->current_scene != NULL) {
        Scene_Ready(state->current_scene);
    }

    while (!Window_ShouldClose(window)) {
        State_Tick(state, window);
        State_Draw(state, window);
    }

    State_Destroy(state);
}

void State_Tick(gg_state_t* state, gg_window_t* window) {
    float delta = Window_GetDeltaTime(window);

    if (state->current_scene != NULL) {
        Scene_Update(state->current_scene, delta);
    }

    if (1.f / delta < 30.f) {
        Log_Warn(Log_TextFormat("Dead frame! (@%.2fFPS)", 1.f / delta));
    }
}

void State_Draw(gg_state_t* state, gg_window_t* window) {
    Window_ClearScreen(window, COL(10, 20, 30));

    if (state->current_scene != NULL) {
        // Background Space Rendering
        Window_BeginParallaxCameraDrawing(window, &state->current_scene->camera, 0.2f);
        { Window_DrawSpaceOrigin(window); }
        Window_EndCameraDrawing(window, &state->current_scene->camera);

        // World Space Rendering
        Window_BeginCameraDrawing(window, &state->current_scene->camera);
        {
            Scene_Draw(state->current_scene, window);
            Window_DrawSpaceOrigin(window);
        }
        Window_EndCameraDrawing(window, &state->current_scene->camera);

        // Screen Space Rendering
        Window_BeginDrawing(window);
        {
            Window_DrawDebugFPS(window);
            Window_DrawSpaceOrigin(window);
        }
        Window_EndDrawing(window);
    }
    else
    {
        Window_BeginDrawing(window);
        {
            Window_DrawRectangle(window, 0, 0, Window_GetWidth(window), Window_GetHeight(window), COL(220, 200, 10));
        }
        Window_EndDrawing(window);
    }
}

void State_Destroy(gg_state_t* state) {}
