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

s16 updateMovementVector(ButtonAction action, s16 currentDirection, s16 moveDirection) {
    if(action == PRESSED) {
        return moveDirection;
    } else if(currentDirection == moveDirection) {
        return 0;
    } else {
        return currentDirection;
    }
}

void characterJoystick(Character* character, JoystickAction *joystickAction) {
    switch (joystickAction->mButton) {
        case LEFT:
            character->mMovementVector.x = updateMovementVector(joystickAction->mAction,
                                                                character->mMovementVector.x,
                                                                -1);
            break;
        case RIGHT:
            character->mMovementVector.x = updateMovementVector(joystickAction->mAction,
                                                                character->mMovementVector.x,
                                                                1);
            break;
        case UP:
            character->mMovementVector.y = updateMovementVector(joystickAction->mAction,
                                                                character->mMovementVector.y,
                                                                -1);
            break;
        case DOWN:
            character->mMovementVector.y = updateMovementVector(joystickAction->mAction,
                                                                character->mMovementVector.y,
                                                                1);
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

// todo: switch to hide/show mechanics
void setActiveSpriteAndPosition(Character *character, Camera* camera, CharacterSprite sprite) {
    SPR_setPosition(character->mWalkingSprite, -8, -8);
    SPR_setPosition(character->mIdleUpSprite, -8, -8);
    SPR_setPosition(character->mIdleDownSprite, -8, -8);
    switch (sprite) {
        case IDLE_DOWN:
            SPR_setPosition(character->mIdleDownSprite,
                            character->mPosition.x + camera->mPosition.x,
                            character->mPosition.y - camera->mPosition.y);
            break;
        case IDLE_UP:
            SPR_setPosition(character->mIdleUpSprite,
                            character->mPosition.x + camera->mPosition.x,
                            character->mPosition.y - camera->mPosition.y);
            break;
        case WALKING_HORIZONTAL:
            SPR_setPosition(character->mWalkingSprite,
                            character->mPosition.x + camera->mPosition.x,
                            character->mPosition.y - camera->mPosition.y);
            break;
    }
}

void updateCharacterSprite(Character *character, Camera* camera) {

    switch (character->mLookDirection) {
        case LOOK_LEFT:
            SPR_setHFlip(character->mWalkingSprite, 0);
            setActiveSpriteAndPosition(character, camera, WALKING_HORIZONTAL);
            break;
        case LOOK_UP:
            setActiveSpriteAndPosition(character, camera, IDLE_UP);
            break;
        case LOOK_RIGHT:
            SPR_setHFlip(character->mWalkingSprite, 1);
            setActiveSpriteAndPosition(character, camera, WALKING_HORIZONTAL);
            break;
        case LOOK_DOWN:
            setActiveSpriteAndPosition(character, camera, IDLE_DOWN);
            break;
    }
}