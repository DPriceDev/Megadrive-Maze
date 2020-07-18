//
// Created by David Price on 14/07/2020.
//

#include "level_one.h"

#include <genesis.h>
#include "resource.h"

// todo: extract to map variable / make level loader generic
void loadLevelOne() {

    s8 roomOne[] = {
            2,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  2,
            2, 14, 13, 14, 13, 14, 13, 14, 13, 14, 13,  2,
            2, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,  2,
            2, 16, 16, 21, 21, 21, 16, 16, 48, 56, 16,  2,
            2, 19, 16, 21, 26, 21, 16, 48, 56, 16, 48,  3,
            2, 19, 16, 21, 21, 21, 16, 56, 56, 48, 48,  13,
            2, 19, 16, 16, 16, 16, 16, 48, 56, 48, 16,  16,
            2, 19, 19, 19, 16, 16, 16, 16, 48, 16, 16,  2,
            2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
            14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
            47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47
    };

    s8 roomTwo[] = {
            2,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  2,
            3,  14, 15, 14, 14, 14, 13, 14, 14, 14, 13, 2,
            13, 16, 16, 16, 16, 16, 16, 16, 16, 48, 16, 2,
            16, 16, 16, 56, 16,  2,  2, 16, 16, 16, 48, 2,
            2,  16, 56, 16, 16,  2,  2, 16, 16, 48, 16, 2,
            2,  16, 16, 56, 16,  2,  2, 16, 16, 16, 48, 2,
            2,  16, 16, 16, 16, 13, 13, 16, 16, 16, 16, 2,
            2,  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 2,
            2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
            14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
            47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47
    };

    s8 corridorOneToTwo[] = {
            3, 3, 3,
            15, 15, 15,
            16, 16, 16,
            2, 2, 2,
            14, 14, 14,
            47, 47, 47
    };

    VDP_setBackgroundColor(2);

    VDP_setPalette(PAL2, tilemap.palette->data);
    VDP_loadTileSet(tilemap.tileset,1,CPU);

    for(int r = 0; r < 11; r++) {
        for(int c = 0; c < 12; c++) {
            int index = (r * 12) + c;
            VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, roomOne[index]), c + 2, r + 2);
        }
    }

    for(int r = 0; r < 11; r++) {
        for(int c = 0; c < 12; c++) {
            int index = (r * 12) + c;
            VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, roomTwo[index]), c + 2 + 15, r + 2 + 3);
        }
    }

    for(int r = 0; r < 6; r++) {
        for(int c = 0; c < 3; c++) {
            int index = (r * 3) + c;
            VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, corridorOneToTwo[index]), c + 2 + 12, r + 2 + 4);
        }
    }

    /* load player sprite */
}