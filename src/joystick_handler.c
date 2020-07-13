//
// Created by David Price on 13/07/2020.
//

#include "joystick_handler.h"

#include <genesis.h>

void joystickHandler(u16 joystick, u16 changed, u16 state) {
    if (joystick == JOY_1) {
        joystickOneHandler(joystick, changed, state);
    } else {
        joystickTwoHandler(joystick, changed, state);
    }
}

void joystickOneHandler(u16 joystick, u16 changed, u16 state) {

    if (state & BUTTON_START) {
        VDP_drawText("player one start pressed", 12, 8);
    } else if(changed & BUTTON_START) {
        VDP_drawText("player one start released", 12, 8);
    }
}

void joystickTwoHandler(u16 joystick, u16 changed, u16 state) {
    if (state & BUTTON_START) {
        VDP_drawText("player two start pressed", 12, 8);
    }
    else if (changed & BUTTON_START) {
        VDP_drawText("player two start released", 12, 8);
    }
}