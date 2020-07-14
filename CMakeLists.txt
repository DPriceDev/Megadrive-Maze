cmake_minimum_required(VERSION 3.10)

set(HEADER_FILES
        inc
        res
        lib
        depends/sgdk/inc
        depends/sgdk/res)

set(SRC
        src/main.c
        src/level_one.c
        src/joystick_handler.c
        src/boot/rom_head.c)

project(Megadrive-Maze)

add_custom_target(megadrive-maze ALL
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/depends/sgdk/bin/make.exe -f ${CMAKE_CURRENT_SOURCE_DIR}/depends/sgdk/makefile.gen
        DEPENDS ${HEADER_FILES}
        SOURCES ${SRC}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(dummy ${SRC} ${HEADER_FILES})
target_include_directories(dummy PUBLIC ${HEADER_FILES})