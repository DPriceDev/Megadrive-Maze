//
// Created by urban on 18/07/2020.
//

#include "camera.h"

Camera* createCamera() {
    Camera* camera;
    camera = MEM_alloc(sizeof *camera);
    V2s16 zeroVector = { 0, 0 };
    camera->mPosition = zeroVector;
    return camera;
}