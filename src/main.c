//
// Created by David Price on 13/07/2020.
//

#include <genesis.h>

#include "resource.h"
#include "character.h"
#include "joystick_handler.h"

int main() {

    /* Initialize joysticks */
    JOY_init();
    JOY_setEventHandler(&joystickHandler);

    /* Initialize Sprite Engine */
    SPR_init(0, 0, 0);

    /* Pregame */
    VDP_drawText("MegaDrive Maze!", 10, 10);

    VDP_setPalette(PAL1, axeman.palette->data);

    struct Character person;
    person.mSprite = SPR_addSprite(&axeman, person.mX, person.mY, TILE_ATTR(PAL1, 0, FALSE, FALSE));

    /* Main Loop */
    while (TRUE) {
        SPR_update();
        VDP_waitVSync();
    }
    return 0;
}