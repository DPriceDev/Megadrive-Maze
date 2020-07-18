//
// Created by David Price on 13/07/2020.
//

#ifndef MEGADRIVE_MAZE_JOYSTICK_HANDLER_H
#define MEGADRIVE_MAZE_JOYSTICK_HANDLER_H

#include <genesis.h>

typedef enum {
    PRESSED,
    RELEASED
} ButtonAction;

typedef enum {
    LEFT = BUTTON_LEFT,
    RIGHT = BUTTON_RIGHT,
    UP = BUTTON_UP,
    DOWN = BUTTON_DOWN
} Button;

typedef struct {
    Button mButton;
    ButtonAction mAction;
} JoystickAction;

typedef struct {
    void (*mJoystickMethod)(void*, JoystickAction*);
    void* mJoyStickController;
} JoystickHandler;

JoystickHandler* createJoystickHandler(void* controller, void (*joystickMethod)(void*, JoystickAction*));
void setJoystickOneHandler(JoystickHandler* handler);
void setJoystickTwoHandler(JoystickHandler* handler);

void joystickHandler(u16 joystick, u16 changed, u16 state);
void dispatchJoystickUpdate(JoystickHandler* handler, u16 changed, u16 state);
void dispatchButtonActionToJoystick(JoystickHandler* handler, Button button, u16 changed, u16 state);
JoystickAction* createJoystickAction(Button button, ButtonAction action);

#endif //MEGADRIVE_MAZE_JOYSTICK_HANDLER_H
