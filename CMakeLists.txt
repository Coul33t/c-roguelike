cmake_minimum_required(VERSION 2.6.0)

if (UNIX)
    find_package(Curses REQUIRED)
endif()

if (WIN32)
    include_directories(../extlib/pdcurses/include/)
    link_directories(../extlib/pdcurses/lib)
endif()

# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(oboyrog C)

set (APP_SRC    oboyrog/main.c

                oboyrog/include_curses.c
             
                oboyrog/input_handler.c

                oboyrog/dungeon/tile.c
                oboyrog/dungeon/dungeon.c

                oboyrog/entity.c

                oboyrog/renderer.c

                oboyrog/fov.c

                oboyrog/tools.c)

add_executable(oboyrog ${APP_SRC})

if (UNIX)
    target_link_libraries(oboyrog -lncurses)
endif()

if (WIN32)
    target_link_libraries(oboyrog -lpdcurses)
endif()

set_property(TARGET oboyrog PROPERTY C_STANDARD 23)
