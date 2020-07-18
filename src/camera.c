//
// Created by urban on 18/07/2020.
//

#include "camera.h"

Camera* createCamera() {
    Camera* camera;
    camera = MEM_alloc(sizeof *camera);
    camera->mPosition = (V2s16) { 0, 0 };
    return camera;
}