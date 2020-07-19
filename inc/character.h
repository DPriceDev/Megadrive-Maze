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

typedef enum {
    IDLE_DOWN = 0,
    IDLE_UP = 1,
    WALKING_HORIZONTAL = 2
} CharacterSprite;

typedef struct {
    Sprite* mSprite;
    V2s16 mPosition;
    V2s16 mMovementVector;
    LookDirection mLookDirection;
} Character;

Character *createCharacter(const SpriteDefinition *spriteDefinition);

void characterTick(Character *character, Camera* camera);
void updateCharacterSprite(Character *character, const Camera* camera);
void characterJoystick(Character* character, const JoystickAction *joystickAction);

s16 updateMovementVector(ButtonAction action, s16 currentDirection, s16 moveDirection);

#endif //MEGADRIVE_MAZE_CHARACTER_H
