add_library(gg_platform STATIC

    camera.c
    texture.c
    tiled.c
    tilemap.c
    tileset.c
    window.c

    )
target_link_libraries(gg_platform raylib)