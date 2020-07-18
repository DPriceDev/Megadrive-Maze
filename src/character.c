//
// Created by urban on 17/07/2020.
//

#include "character.h"
#include "string.h"

struct Character *createCharacter() {
    struct Character *character;
    character = MEM_alloc(sizeof *character);
    character->mX = 7 * 8;
    character->mY = 7 * 8;
    character->mIdleDownSprite = SPR_addSprite(&PlayerIdleDownSprite, character->mX, character->mY, TILE_ATTR(PAL1, 1, 0, 0));
    character->mWalkingSprite = SPR_addSprite(&PlayerWalkingSprite, -8, -8, TILE_ATTR(PAL1, 1, 0, 0));
    character->mIdleUpSprite = SPR_addSprite(&PlayerIdleUpSprite, -8, -8, TILE_ATTR(PAL1, 1, 0, 0));
    struct MovementVector vector = {0, 0 };
    character->mMovementVector = vector;
    character->mLookDirection = LOOK_DOWN;
    return character;
}

//todo: refactor smaller - duplication
void characterJoystick(struct Character* character, struct JoystickAction *joystickAction) {
    switch (joystickAction->mButton) {
        case LEFT:
            if(joystickAction->mAction == PRESSED) {
                character->mMovementVector.mX = -1;
            } else {
                character->mMovementVector.mX = 0;
            }
            break;
        case RIGHT:
            if(joystickAction->mAction == PRESSED) {
                character->mMovementVector.mX = 1;
            } else {
                character->mMovementVector.mX = 0;
            }
            break;
        case UP:
            if(joystickAction->mAction == PRESSED) {
                character->mMovementVector.mY = -1;
            } else {
                character->mMovementVector.mY = 0;
            }
            break;
        case DOWN:
            if(joystickAction->mAction == PRESSED) {
                character->mMovementVector.mY = 1;
            } else {
                character->mMovementVector.mY = 0;
            }
            break;
    }
}

void characterTick(struct Character *character) {
    updatePosition(character);
}

void setLookDirectionFromMovementVector(struct Character *character) {
    if(character->mMovementVector.mX > 0) {
        character->mLookDirection = LOOK_RIGHT;
    } else if(character->mMovementVector.mX < 0) {
        character->mLookDirection = LOOK_LEFT;
    } else if(character->mMovementVector.mY < 0) {
        character->mLookDirection = LOOK_UP;
    } else {
        character->mLookDirection = LOOK_DOWN;
    }
}

//todo: refactor smaller - duplication
void updatePosition(struct Character *character) {
    character->mX += character->mMovementVector.mX;
    character->mY += character->mMovementVector.mY;
    setLookDirectionFromMovementVector(character);

    switch (character->mLookDirection) {
        case LOOK_LEFT:
            SPR_setHFlip(character->mWalkingSprite, 0);
            SPR_setPosition(character->mWalkingSprite, character->mX, character->mY);
            SPR_setPosition(character->mIdleUpSprite, -8, -8);
            SPR_setPosition(character->mIdleDownSprite, -8, -8);
            break;
        case LOOK_UP:
            SPR_setPosition(character->mIdleUpSprite, character->mX, character->mY);
            SPR_setPosition(character->mIdleDownSprite, -8, -8);
            SPR_setPosition(character->mWalkingSprite, -8, -8);
            break;
        case LOOK_RIGHT:
            SPR_setHFlip(character->mWalkingSprite, 1);
            SPR_setPosition(character->mWalkingSprite, character->mX, character->mY);
            SPR_setPosition(character->mIdleDownSprite, -8, -8);
            SPR_setPosition(character->mIdleUpSprite, -8, -8);
            break;
        case LOOK_DOWN:
            SPR_setPosition(character->mIdleDownSprite, character->mX, character->mY);
            SPR_setPosition(character->mIdleUpSprite, -8, -8);
            SPR_setPosition(character->mWalkingSprite, -8, -8);
            break;
    }
}