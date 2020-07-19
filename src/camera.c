//
// Created by urban on 18/07/2020.
//

#include "camera.h"

static const s16 sBoundingBox = 32;
static const V2s16 sPalViewport = { 256, 240 };

Camera* createCamera() {
    Camera* camera;
    camera = MEM_alloc(sizeof *camera);
    camera->mPosition = (V2s16) { 0, 0 };
    camera->mTargetPosition = (V2s16) { 0, 0 };
    camera->mSize = sPalViewport;
    return camera;
}

// todo: refactor smaller / duplication
void updateCameraScrollPosition(Camera* camera) {

    if(camera->mTargetPosition.x - camera->mPosition.x < -sBoundingBox) {
        camera->mPosition.x -= 1;
    } else if(camera->mTargetPosition.x - camera->mPosition.x > sBoundingBox) {
        camera->mPosition.x += 1;
    }

    if(camera->mTargetPosition.y - camera->mPosition.y < -sBoundingBox) {
        camera->mPosition.y -= 1;
    } else if(camera->mTargetPosition.y - camera->mPosition.y > sBoundingBox) {
        camera->mPosition.y += 1;
    }

    VDP_setHorizontalScroll(BG_B, camera->mPosition.x);
    VDP_setVerticalScroll(BG_B, camera->mPosition.y);
}

void centerCameraOnPoint(Camera* camera, const V2s16 point) {
    camera->mPosition.x = -point.x + (camera->mSize.x / 2);
    camera->mPosition.y = point.y - (camera->mSize.y / 2);
    camera->mTargetPosition = camera->mPosition;
}