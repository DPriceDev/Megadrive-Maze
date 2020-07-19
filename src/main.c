//
// Created by David Price on 13/07/2020.
//

#include <genesis.h>

#include "level_one.h"
#include "camera.h"
#include "world.h"
#include "character.h"
#include "joystick_handler.h"

#include "resource.h"

int main() {

    /* initialise video display processor */
    VDP_init();
    VDP_setScreenWidth256();
    VDP_setScreenHeight240();
    VDP_setPlaneSize(64, 64, TRUE);

    /* Initialize joysticks */
    JOY_init();
    JOY_setEventHandler(&joystickHandler);

    /* Initialize Sprite Engine */
    SPR_init(0, 0, 0);

    /*
     * Pre-game
     */

    /* Create character and assign controller */
    VDP_setPalette(PAL1, player.palette->data);
    Character *character = createCharacter(&player);
    character->mPosition = (V2s16) { 7 * 8, 7 * 8 };

    JoystickHandler* joyHandler = createJoystickHandler(character,
            (void (*)(void *, JoystickAction *)) characterJoystick);
    setJoystickOneHandler(joyHandler);

    /* create camera and world and center camera on player */
    World *world = createWorld();
    centerCameraOnPoint(world->mCamera, character->mPosition);

    /* Load first level */
    loadLevelOne(world->mMap);

    /* Main Loop */
    bool isRunning = TRUE;
    while (isRunning) {
        characterTick(character, world->mCamera);

        updateCharacterSprite(character, world->mCamera);
        updateCameraScrollPosition(world->mCamera);
        SPR_update();
        VDP_waitVSync();
    }

    /* deallocate */
    // todo: deallocate internal pointers, deconstuctor method?
    MEM_free(world);
    MEM_free(character);
    MEM_free(joyHandler);
    return 0;
}