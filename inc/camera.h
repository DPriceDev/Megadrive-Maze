//
// Created by urban on 18/07/2020.
//

#ifndef MEGADRIVE_MAZE_CAMERA_H
#define MEGADRIVE_MAZE_CAMERA_H

#include <genesis.h>

typedef struct {
    V2s16 mPosition;
} Camera;

Camera* createCamera();

#endif //MEGADRIVE_MAZE_CAMERA_H
