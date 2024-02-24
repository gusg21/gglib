set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

add_library(gglib STATIC

    actor.c
    assets.c
    camera.c
    grid.c
    keys.c
    ldefs.c
    log.c
    scene.c
    scripting.c
    state.c
    texture.c
    tiled.c
    tiledobject.c
    tileset.c
    transform.c
    vector.c
    window.c

    )

add_subdirectory(lua54)
target_link_libraries(gglib lua54)

add_subdirectory(raylib)
target_link_libraries(gglib raylib)

add_subdirectory(parson)
target_link_libraries(gglib parson)

add_subdirectory(rlImGui)
target_link_libraries(gglib rlImGui)