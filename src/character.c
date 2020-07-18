//
// Created by urban on 17/07/2020.
//

#include "character.h"
#include "string.h"

Character *createCharacter() {
    Character *character;
    character = MEM_alloc(sizeof *character);

    V2s16 zeroVector = { 0, 0 };
    character->mMovementVector = zeroVector;
    character->mMovementVector = zeroVector;

    character->mIdleDownSprite = SPR_addSprite(&PlayerIdleDownSprite,
                                               character->mPosition.x,
                                               character->mPosition.y,
                                               TILE_ATTR(PAL1, 1, 0, 0));

    character->mWalkingSprite = SPR_addSprite(&PlayerWalkingSprite, -8, -8, TILE_ATTR(PAL1, 1, 0, 0));
    character->mIdleUpSprite = SPR_addSprite(&PlayerIdleUpSprite, -8, -8, TILE_ATTR(PAL1, 1, 0, 0));

    character->mLookDirection = LOOK_DOWN;
    return character;
}

//todo: refactor smaller - duplication
void characterJoystick(Character* character, JoystickAction *joystickAction) {
    switch (joystickAction->mButton) {
        case LEFT:
            if(joystickAction->mAction == PRESSED) {
                character->mMovementVector.x = -1;
            } else {
                character->mMovementVector.x = 0;
            }
            break;
        case RIGHT:
            if(joystickAction->mAction == PRESSED) {
                character->mMovementVector.x = 1;
            } else {
                character->mMovementVector.x = 0;
            }
            break;
        case UP:
            if(joystickAction->mAction == PRESSED) {
                character->mMovementVector.y = -1;
            } else {
                character->mMovementVector.y = 0;
            }
            break;
        case DOWN:
            if(joystickAction->mAction == PRESSED) {
                character->mMovementVector.y = 1;
            } else {
                character->mMovementVector.y = 0;
            }
            break;
    }
}

void characterTick(Character *character) {
    updatePosition(character);
}

void setLookDirectionFromMovementVector(Character *character) {
    if(character->mMovementVector.x > 0) {
        character->mLookDirection = LOOK_RIGHT;
    } else if(character->mMovementVector.x < 0) {
        character->mLookDirection = LOOK_LEFT;
    } else if(character->mMovementVector.y < 0) {
        character->mLookDirection = LOOK_UP;
    } else {
        character->mLookDirection = LOOK_DOWN;
    }
}

//todo: refactor smaller - duplication
void updatePosition(Character *character) {
    character->mPosition.x += character->mMovementVector.x;
    character->mPosition.y += character->mMovementVector.y;
    setLookDirectionFromMovementVector(character);

    switch (character->mLookDirection) {
        case LOOK_LEFT:
            SPR_setHFlip(character->mWalkingSprite, 0);
            SPR_setPosition(character->mWalkingSprite, character->mPosition.x, character->mPosition.y);
            SPR_setPosition(character->mIdleUpSprite, -8, -8);
            SPR_setPosition(character->mIdleDownSprite, -8, -8);
            break;
        case LOOK_UP:
            SPR_setPosition(character->mIdleUpSprite, character->mPosition.x, character->mPosition.y);
            SPR_setPosition(character->mIdleDownSprite, -8, -8);
            SPR_setPosition(character->mWalkingSprite, -8, -8);
            break;
        case LOOK_RIGHT:
            SPR_setHFlip(character->mWalkingSprite, 1);
            SPR_setPosition(character->mWalkingSprite, character->mPosition.x, character->mPosition.y);
            SPR_setPosition(character->mIdleDownSprite, -8, -8);
            SPR_setPosition(character->mIdleUpSprite, -8, -8);
            break;
        case LOOK_DOWN:
            SPR_setPosition(character->mIdleDownSprite, character->mPosition.x, character->mPosition.y);
            SPR_setPosition(character->mIdleUpSprite, -8, -8);
            SPR_setPosition(character->mWalkingSprite, -8, -8);
            break;
    }
}