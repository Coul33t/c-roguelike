cmake_minimum_required(VERSION 2.6.0)
    
# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(oboyrog C)

SET (APP_SRC    oboyrog/main.c
             
                oboyrog/input_handler.c

                oboyrog/dungeon/tile.c
                oboyrog/dungeon/dungeon.c

                oboyrog/renderer.c

                oboyrog/tools.c)

add_executable(oboyrog ${APP_SRC})
target_link_libraries(oboyrog -lncurses)