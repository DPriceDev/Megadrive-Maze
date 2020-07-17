//
// Created by David Price on 13/07/2020.
//

#include "joystick_handler.h"

#include <genesis.h>

void (*joystickOneFunPointer)(struct JoystickAction*);

void setJoystickOneFunction(void (*functionPointer)(struct JoystickAction*)) {
    joystickOneFunPointer = functionPointer;
}

struct JoystickAction* createJoystickAction(enum Button button, enum ButtonAction action) {
    struct JoystickAction* joystickAction = MEM_alloc(sizeof *joystickAction);
    joystickAction->mAction = action;
    joystickAction->mButton = button;
    return joystickAction;
}

struct JoystickAction* dispatchButtonActionToJoystickOne(enum Button button, u16 changed, u16 state) {
    if(state & button) {
        joystickOneFunPointer(createJoystickAction(button, PRESSED));
    } else if(changed & button) {
        joystickOneFunPointer(createJoystickAction(button, RELEASED));
    }
}

void joystickHandler(u16 joystick, u16 changed, u16 state) {
    if (joystick == JOY_1) {
        joystickOneHandler(changed, state);
    } else {
        joystickTwoHandler(changed, state);
    }
}

void joystickOneHandler(u16 changed, u16 state) {
    dispatchButtonActionToJoystickOne(LEFT, changed, state);
    dispatchButtonActionToJoystickOne(UP, changed, state);
    dispatchButtonActionToJoystickOne(RIGHT, changed, state);
    dispatchButtonActionToJoystickOne(DOWN, changed, state);
}

void joystickTwoHandler(u16 changed, u16 state) { }