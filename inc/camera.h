//
// Created by urban on 18/07/2020.
//

#ifndef MEGADRIVE_MAZE_CAMERA_H
#define MEGADRIVE_MAZE_CAMERA_H

#include <genesis.h>

typedef struct {
    V2s16 mPosition;
    V2s16 mTargetPosition;
    V2s16 mSize;
} Camera;

Camera* createCamera();

void updateCameraScrollPosition(Camera* camera);

void centerCameraOnPoint(Camera* camera, V2s16 point);

#endif //MEGADRIVE_MAZE_CAMERA_H
