cmake_minimum_required(VERSION 3.10)

set(HEADER_FILES
        inc
        res
        lib
        depends/sgdk/inc
        depends/sgdk/res)

project(Megadrive-Maze)

add_executable(maze src/main.c ${HEADER_FILES})
target_include_directories(maze PUBLIC ${HEADER_FILES})