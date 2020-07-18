//
// Created by David Price on 13/07/2020.
//

#ifndef MEGADRIVE_MAZE_JOYSTICK_HANDLER_H
#define MEGADRIVE_MAZE_JOYSTICK_HANDLER_H

#include <genesis.h>

enum ButtonAction {
    PRESSED,
    RELEASED
};

enum Button {
    LEFT = BUTTON_LEFT,
    RIGHT = BUTTON_RIGHT,
    UP = BUTTON_UP,
    DOWN = BUTTON_DOWN
};

struct JoystickAction {
    enum Button mButton;
    enum ButtonAction mAction;
};

void joystickHandler(u16 joystick, u16 changed, u16 state);
void joystickOneHandler(u16 changed, u16 state);
void joystickTwoHandler(u16 changed, u16 state);

void setJoystickOneFunction(void* controller, void (*functionPointer)(void* controller, struct JoystickAction*));
struct JoystickAction* createJoystickAction(enum Button button, enum ButtonAction action);

#endif //MEGADRIVE_MAZE_JOYSTICK_HANDLER_H
