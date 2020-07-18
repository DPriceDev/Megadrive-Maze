//
// Created by David Price on 13/07/2020.
//

#include "joystick_handler.h"

#include <genesis.h>

void (*joystickOneFunPointer)(void*, struct JoystickAction*);

void* joyStickOneController;

void setJoystickOneFunction(void* controller, void (*functionPointer)(void*, struct JoystickAction*)) {
    joystickOneFunPointer = functionPointer;
    joyStickOneController = controller;
}

struct JoystickAction* createJoystickAction(enum Button button, enum ButtonAction action) {
    struct JoystickAction* joystickAction = MEM_alloc(sizeof *joystickAction);
    joystickAction->mAction = action;
    joystickAction->mButton = button;
    return joystickAction;
}

struct JoystickAction* dispatchButtonActionToJoystickOne(enum Button button, u16 changed, u16 state) {
    if(state & button) {
        joystickOneFunPointer(joyStickOneController, createJoystickAction(button, PRESSED));
    } else if(changed & button) {
        joystickOneFunPointer(joyStickOneController, createJoystickAction(button, RELEASED));
    }
}

void joystickHandler(u16 joystick, u16 changed, u16 state) {
    if (joystick == JOY_1) {
        joystickOneHandler(changed, state);
    } else {
        joystickTwoHandler(changed, state);
    }
}

//todo: refactor smaller - duplication? list?
void joystickOneHandler(u16 changed, u16 state) {
    dispatchButtonActionToJoystickOne(LEFT, changed, state);
    dispatchButtonActionToJoystickOne(UP, changed, state);
    dispatchButtonActionToJoystickOne(RIGHT, changed, state);
    dispatchButtonActionToJoystickOne(DOWN, changed, state);
}

void joystickTwoHandler(u16 changed, u16 state) { }