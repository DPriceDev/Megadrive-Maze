//
// Created by David Price on 13/07/2020.
//

#include "joystick_handler.h"

#include <genesis.h>

struct JoystickHandler* joystickOneHandler;
struct JoystickHandler* joystickTwoHandler;

struct JoystickHandler* createJoystickHandler(void* controller, void (*joystickMethod)(void*, struct JoystickAction*)) {
    struct JoystickHandler *handler;
    handler = MEM_alloc(sizeof *handler);
    handler->mJoyStickController = controller;
    handler->mJoystickMethod = joystickMethod;
    return handler;
}

void setJoystickOneHandler(struct JoystickHandler* handler) {
    joystickOneHandler = handler;
}
void setJoystickTwoHandler(struct JoystickHandler* handler) {
    joystickTwoHandler = handler;
}

struct JoystickAction* createJoystickAction(enum Button button, enum ButtonAction action) {
    struct JoystickAction* joystickAction = MEM_alloc(sizeof *joystickAction);
    joystickAction->mAction = action;
    joystickAction->mButton = button;
    return joystickAction;
}


void joystickHandler(u16 joystick, u16 changed, u16 state) {
    if (joystick == JOY_1) {
        dispatchJoystickUpdate(joystickOneHandler, changed, state);
    } else {
        dispatchJoystickUpdate(joystickTwoHandler, changed, state);
    }
}

//todo: refactor smaller - duplication? list?
void dispatchJoystickUpdate(struct JoystickHandler* handler, u16 changed, u16 state) {
    dispatchButtonActionToJoystick(handler, LEFT, changed, state);
    dispatchButtonActionToJoystick(handler, UP, changed, state);
    dispatchButtonActionToJoystick(handler, RIGHT, changed, state);
    dispatchButtonActionToJoystick(handler, DOWN, changed, state);
}

struct JoystickAction* dispatchButtonActionToJoystick(struct JoystickHandler* handler, enum Button button, u16 changed, u16 state) {
    if(state & button) {
        handler->mJoystickMethod(handler->mJoyStickController, createJoystickAction(button, PRESSED));
    } else if(changed & button) {
        handler->mJoystickMethod(handler->mJoyStickController, createJoystickAction(button, RELEASED));
    }
}