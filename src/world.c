//
// Created by urban on 18/07/2020.
//

#include "world.h"

World* createWorld() {
    World *world;
    world = MEM_alloc(sizeof *world);
    world->mCamera = createCamera();
    return world;
}