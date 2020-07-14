//
// Created by David Price on 13/07/2020.
//

#include <genesis.h>

#include "level_one.h"
#include "joystick_handler.h"


int main() {

    /* initialise video display processor */
    VDP_init();
    VDP_setScreenWidth320();
    VDP_setScreenHeight224();
    VDP_setPlanSize(64, 64);

    /* Initialize joysticks */
    JOY_init();
    JOY_setEventHandler(&joystickHandler);

    /* Initialize Sprite Engine */
    SPR_init(0, 0, 0);

    /* Pre-game */
    loadLevelOne();

    /* Main Loop */
    while (TRUE) {
        SPR_update();
        VDP_waitVSync();
    }
    return 0;
}