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

struct JoystickHandler {
    void (*mJoystickMethod)(void*, struct JoystickAction*);
    void* mJoyStickController;
};

struct JoystickHandler* createJoystickHandler(void* controller, void (*joystickMethod)(void*, struct JoystickAction*));
void setJoystickOneHandler(struct JoystickHandler* handler);
void setJoystickTwoHandler(struct JoystickHandler* handler);

void joystickHandler(u16 joystick, u16 changed, u16 state);
void dispatchJoystickUpdate(struct JoystickHandler* handler, u16 changed, u16 state);
struct JoystickAction* dispatchButtonActionToJoystick(struct JoystickHandler* handler, enum Button button, u16 changed, u16 state);
struct JoystickAction* createJoystickAction(enum Button button, enum ButtonAction action);

#endif //MEGADRIVE_MAZE_JOYSTICK_HANDLER_H
