//
// Created by David Price on 13/07/2020.
//

#ifndef MEGADRIVE_MAZE_CHARACTER_H
#define MEGADRIVE_MAZE_CHARACTER_H

#include <genesis.h>
#include <maths.h>
#include "resource.h"

#include "joystick_handler.h"

typedef enum  {
    LOOK_LEFT,
    LOOK_UP,
    LOOK_RIGHT,
    LOOK_DOWN
} LookDirection;

typedef struct {
    Sprite* mWalkingSprite;
    Sprite* mIdleDownSprite;
    Sprite* mIdleUpSprite;
    V2s16 mPosition;
    V2s16 mMovementVector;
    LookDirection mLookDirection;
} Character;

Character *createCharacter();

void characterTick(Character *character, Camera* camera);

void updateCharacterSprite(Character *character, Camera* camera);

void characterJoystick(Character* character, JoystickAction *joystickAction);

#endif //MEGADRIVE_MAZE_CHARACTER_H
