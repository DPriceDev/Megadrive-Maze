//
// Created by urban on 17/07/2020.
//

#include <world.h>
#include "character.h"
#include "string.h"

Character *createCharacter() {
    Character *character;
    character = MEM_alloc(sizeof *character);

    character->mPosition = (V2s16) { 0, 0 };
    character->mMovementVector = (V2s16) { 0, 0 };

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
            } else if(character->mMovementVector.x == -1) {
                character->mMovementVector.x = 0;
            }
            break;
        case RIGHT:
            if(joystickAction->mAction == PRESSED) {
                character->mMovementVector.x = 1;
            } else if(character->mMovementVector.x == 1) {
                character->mMovementVector.x = 0;
            }
            break;
        case UP:
            if(joystickAction->mAction == PRESSED) {
                character->mMovementVector.y = -1;
            } else if(character->mMovementVector.y == -1) {
                character->mMovementVector.y = 0;
            }
            break;
        case DOWN:
            if(joystickAction->mAction == PRESSED) {
                character->mMovementVector.y = 1;
            } else if(character->mMovementVector.y == 1) {
                character->mMovementVector.y = 0;
            }
            break;
    }
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

void characterTick(Character *character, Camera* camera) {
    character->mPosition.x += character->mMovementVector.x;
    character->mPosition.y += character->mMovementVector.y;
    setLookDirectionFromMovementVector(character);

    camera->mTargetPosition.x -= character->mMovementVector.x;
    camera->mTargetPosition.y += character->mMovementVector.y;
}

//todo: refactor smaller - duplication
void updateCharacterSprite(Character *character, Camera* camera) {

    switch (character->mLookDirection) {
        case LOOK_LEFT:
            SPR_setHFlip(character->mWalkingSprite, 0);
            SPR_setPosition(character->mWalkingSprite,
                            character->mPosition.x + camera->mPosition.x,
                            character->mPosition.y - camera->mPosition.y);
            SPR_setPosition(character->mIdleUpSprite, -8, -8);
            SPR_setPosition(character->mIdleDownSprite, -8, -8);
            break;
        case LOOK_UP:
            SPR_setPosition(character->mIdleUpSprite,
                            character->mPosition.x + camera->mPosition.x,
                            character->mPosition.y - camera->mPosition.y);
            SPR_setPosition(character->mIdleDownSprite, -8, -8);
            SPR_setPosition(character->mWalkingSprite, -8, -8);
            break;
        case LOOK_RIGHT:
            SPR_setHFlip(character->mWalkingSprite, 1);
            SPR_setPosition(character->mWalkingSprite,
                            character->mPosition.x + camera->mPosition.x,
                            character->mPosition.y - camera->mPosition.y);
            SPR_setPosition(character->mIdleDownSprite, -8, -8);
            SPR_setPosition(character->mIdleUpSprite, -8, -8);
            break;
        case LOOK_DOWN:
            SPR_setPosition(character->mIdleDownSprite,
                            character->mPosition.x + camera->mPosition.x,
                            character->mPosition.y - camera->mPosition.y);
            SPR_setPosition(character->mIdleUpSprite, -8, -8);
            SPR_setPosition(character->mWalkingSprite, -8, -8);
            break;
    }
}