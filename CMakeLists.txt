cmake_minimum_required(VERSION 3.10)

set(HEADER_FILES
        inc
        res
        lib
        depends/sgdk/inc
        depends/sgdk/res)

set(SRC
        src/main.c
        src/joystick_handler.c
        src/boot/rom_head.c)

project(Megadrive-Maze)

add_executable(maze ${SRC} ${HEADER_FILES})
target_include_directories(maze PUBLIC ${HEADER_FILES})