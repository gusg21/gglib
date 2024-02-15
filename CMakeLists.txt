add_library(gglib STATIC

    camera.c
    grid.c
    log.c
    scene.c
    texture.c
    tiled.c
    tiledobject.c
    tileset.c
    transform.c
    vector.c
    window.c

    )
target_link_libraries(gglib raylib)