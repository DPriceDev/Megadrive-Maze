//
// Created by urban on 17/07/2020.
//

#include <world.h>
#include "character.h"
#include "string.h"

Character *createCharacter(const SpriteDefinition *spriteDefinition) {
    Character *character;
    character = MEM_alloc(sizeof *character);

    character->mPosition = (V2s16) { 0, 0 };
    character->mMovementVector = (V2s16) { 0, 0 };

    character->mSprite = SPR_addSprite(spriteDefinition,
                                       character->mPosition.x,
                                       character->mPosition.y,
                                       TILE_ATTR(PAL1, 1, 0, 0));
    character->mLookDirection = LOOK_DOWN;
    return character;
}

s16 updateMovementVector(const ButtonAction action, const s16 currentDirection, const s16 moveDirection) {
    if(action == PRESSED) {
        return moveDirection;
    } else if(currentDirection == moveDirection) {
        return 0;
    } else {
        return currentDirection;
    }
}

void characterJoystick(Character* character, const JoystickAction *joystickAction) {
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

void updateCharacterSprite(Character *character, const Camera* camera) {
    SPR_setPosition(character->mSprite,
                    character->mPosition.x + camera->mPosition.x,
                    character->mPosition.y - camera->mPosition.y);
    switch (character->mLookDirection) {
        case LOOK_LEFT:
            SPR_setHFlip(character->mSprite, 0);
            SPR_setAnim(character->mSprite, WALKING_HORIZONTAL);
            break;
        case LOOK_UP:
            SPR_setAnim(character->mSprite, IDLE_UP);
            break;
        case LOOK_RIGHT:
            SPR_setHFlip(character->mSprite, 1);
            SPR_setAnim(character->mSprite, WALKING_HORIZONTAL);

            break;
        case LOOK_DOWN:
            SPR_setAnim(character->mSprite, IDLE_DOWN);
            break;
    }
}