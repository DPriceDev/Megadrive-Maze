cmake_minimum_required(VERSION 3.10)

project(Megadrive-Maze)

set(HEADER_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        ${CMAKE_CURRENT_SOURCE_DIR}/depends/sgdk
        ${CMAKE_CURRENT_SOURCE_DIR}/depends/sgdk/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/depends/sgdk/res)

set(SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/level_one.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/joystick_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/boot/rom_head.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/character.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/camera.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/world.c)

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    set(type debug)
ELSE()
    set(type clean release)
ENDIF()

set(SGDK_COMPILE_COMMAND
        ${CMAKE_CURRENT_SOURCE_DIR}/depends/sgdk/bin/make.exe
        GDK=C:/Projects/Prog_SegaMegaDriveGame/Megadrive-Maze/depends/sgdk
        GDK_WIN=C:\\Projects\\Prog_SegaMegaDriveGame\\Megadrive-Maze\\depends\\sgdk
        -f ${CMAKE_CURRENT_SOURCE_DIR}/depends/sgdk/makelib.gen
        ${type})

set(PROJECT_COMPILE_COMMAND
        ${CMAKE_CURRENT_SOURCE_DIR}/depends/sgdk/bin/make.exe
        GDK=C:/Projects/Prog_SegaMegaDriveGame/Megadrive-Maze/depends/sgdk
        GDK_WIN=C:\\Projects\\Prog_SegaMegaDriveGame\\Megadrive-Maze\\depends\\sgdk
        -f ${CMAKE_CURRENT_SOURCE_DIR}/depends/sgdk/makefile.gen
        ${type})

add_custom_target(megadrive-maze ALL ${SGDK_COMPILE_COMMAND}
        COMMAND ${PROJECT_COMPILE_COMMAND}
        DEPENDS ${HEADER_FILES}
        SOURCES ${SRC}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(dummy ${SRC})
target_include_directories(dummy PUBLIC ${HEADER_FILES})