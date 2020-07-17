//
// Created by David Price on 13/07/2020.
//

#ifndef MEGADRIVE_MAZE_CHARACTER_H
#define MEGADRIVE_MAZE_CHARACTER_H

#include <genesis.h>
#include "resource.h"

#include "joystick_handler.h"

enum LookDirection {
    LOOK_LEFT,
    LOOK_UP,
    LOOK_RIGHT,
    LOOK_DOWN
};

struct MovementVector {
    int mX;
    int mY;
};

struct Character {
    Sprite* mWalkingSprite;
    Sprite* mIdleDownSprite;
    Sprite* mIdleUpSprite;
    enum LookDirection mLookDirection;
    int mX, mY;
    struct MovementVector mMovementVector;
};

struct Character *initCharacter();

void characterTick();

void updatePosition();

void characterJoystick(struct JoystickAction* joystickAction);

#endif //MEGADRIVE_MAZE_CHARACTER_H
