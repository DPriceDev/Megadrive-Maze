cmake_minimum_required(VERSION 3.10)

set(HEADER_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/depends/sgdk/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/depends/sgdk/res)

set(SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/level_one.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/joystick_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/boot/rom_head.c src/character.c)

project(Megadrive-Maze)

add_custom_target(megadrive-maze ALL
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/depends/sgdk/bin/make.exe -f ${CMAKE_CURRENT_SOURCE_DIR}/depends/sgdk/makefile.gen
        DEPENDS ${HEADER_FILES}
        SOURCES ${SRC}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(dummy ${SRC})
target_include_directories(dummy PUBLIC ${HEADER_FILES})