//
// Created by David Price on 13/07/2020.
//

#ifndef MEGADRIVE_MAZE_JOYSTICK_HANDLER_H
#define MEGADRIVE_MAZE_JOYSTICK_HANDLER_H

#include <genesis.h>

void joystickHandler(u16 joystick, u16 changed, u16 state);
void joystickOneHandler(u16 changed, u16 state);
void joystickTwoHandler(u16 changed, u16 state);

#endif //MEGADRIVE_MAZE_JOYSTICK_HANDLER_H
