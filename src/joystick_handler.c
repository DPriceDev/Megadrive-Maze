//
// Created by David Price on 13/07/2020.
//

#include "joystick_handler.h"

#include <genesis.h>

void joystickHandler(u16 joystick, u16 changed, u16 state) {
    if (joystick == JOY_1) {
        joystickOneHandler(changed, state);
    } else {
        joystickTwoHandler(changed, state);
    }
}

void joystickOneHandler(u16 changed, u16 state) {
    if(state & BUTTON_LEFT) {
        VDP_setHorizontalScroll(BG_B, 0);
    } else if(changed & BUTTON_LEFT) {

    }

    if(state & BUTTON_RIGHT) {
        VDP_setHorizontalScroll(BG_B, 8);
    } else if(changed & BUTTON_RIGHT) {

    }
}

void joystickTwoHandler(u16 changed, u16 state) { }