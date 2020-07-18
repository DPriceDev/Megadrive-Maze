//
// Created by urban on 18/07/2020.
//

#ifndef MEGADRIVE_MAZE_WORLD_H
#define MEGADRIVE_MAZE_WORLD_H

#include <genesis.h>
#include "camera.h"

typedef struct {
    Camera* mCamera;
    s8 mMap[64 * 64];
} World;

World* createWorld();

#endif //MEGADRIVE_MAZE_WORLD_H
