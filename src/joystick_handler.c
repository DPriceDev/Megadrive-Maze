//
// Created by David Price on 13/07/2020.
//

#include "joystick_handler.h"

#include <genesis.h>

JoystickHandler* joystickOneHandler;
JoystickHandler* joystickTwoHandler;

JoystickHandler* createJoystickHandler(void* controller, void (*joystickMethod)(void*, JoystickAction*)) {
    JoystickHandler *handler;
    handler = MEM_alloc(sizeof *handler);
    handler->mJoyStickController = controller;
    handler->mJoystickMethod = joystickMethod;
    return handler;
}

void setJoystickOneHandler(JoystickHandler* handler) {
    joystickOneHandler = handler;
}
void setJoystickTwoHandler(JoystickHandler* handler) {
    joystickTwoHandler = handler;
}

JoystickAction* createJoystickAction(Button button, ButtonAction action) {
    JoystickAction* joystickAction = MEM_alloc(sizeof *joystickAction);
    joystickAction->mAction = action;
    joystickAction->mButton = button;
    return joystickAction;
}


void joystickHandler(u16 joystick, u16 changed, u16 state) {
    if (joystick == JOY_1) {
        dispatchJoystickUpdate(joystickOneHandler, changed, state);
    } else {
        if(joystickTwoHandler != NULL) {
            dispatchJoystickUpdate(joystickTwoHandler, changed, state);
        }
    }
}

//todo: refactor smaller - duplication? list?
void dispatchJoystickUpdate(JoystickHandler* handler, u16 changed, u16 state) {
    dispatchButtonActionToJoystick(handler, LEFT, changed, state);
    dispatchButtonActionToJoystick(handler, UP, changed, state);
    dispatchButtonActionToJoystick(handler, RIGHT, changed, state);
    dispatchButtonActionToJoystick(handler, DOWN, changed, state);
}

void dispatchButtonActionToJoystick(JoystickHandler* handler, Button button, u16 changed, u16 state) {
    if(state & button) {
        handler->mJoystickMethod(handler->mJoyStickController, createJoystickAction(button, PRESSED));
    } else if(changed & button) {
        handler->mJoystickMethod(handler->mJoyStickController, createJoystickAction(button, RELEASED));
    }
}