add_library(gglib STATIC

    actor.c
    assets.c
    camera.c
    grid.c
    ldefs.c
    log.c
    scene.c
    scripting.c
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