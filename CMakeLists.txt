cmake_minimum_required(VERSION 2.8.12)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(oboyrog C)

if (UNIX)
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
endif()

if (WIN32)
    include_directories(../extlib/pdcurses/include/)
    link_directories(../extlib/pdcurses/lib)
endif()

set (APP_SRC    oboyrog/main.c

                oboyrog/include_curses.c
             
                oboyrog/input_handler/input_handler.c

                oboyrog/dungeon/tile.c
                oboyrog/dungeon/dungeon.c

                oboyrog/entity.c

                oboyrog/messages/message.c
                oboyrog/messages/messages_manager.c
              
                oboyrog/renderer.c
                
                oboyrog/fov.c

                oboyrog/targeting_list.c

                oboyrog/tools/tools.c)

add_executable(oboyrog ${APP_SRC})

if(MSVC)
  target_compile_options(oboyrog PRIVATE /W4 /WX)
else()
  target_compile_options(oboyrog PRIVATE -Wall -Wextra -Wpedantic)
endif()

if (UNIX)
    target_link_libraries(oboyrog -lncurses -lm)
endif()

if (WIN32)
    target_link_libraries(oboyrog -lpdcurses -lm)
endif()

set_property(TARGET oboyrog PROPERTY C_STANDARD 23)
