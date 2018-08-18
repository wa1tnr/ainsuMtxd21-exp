/* Code generated from Atmel Start - overwritten; do make a copy. */

/* warm.c */

/* wa1tnr - August, 2018 LGPL v2.1 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"
#include "warm.h" // io descriptor
#include "common.h"

/* Terminal Input Buffer for interpreter */
// #define maxtib 16

// struct io_descriptor *io;

int state_warm = 0;

void _warm(void) { // reboot the machine
    io_write(io, (uint8_t *)"  WARM BOOT \r\n", 14);
    NVIC_SystemReset();      // processor software reset
}

void capture_warm(void) { // trap keystrokes to build a command

/*
    if (state_warm == -2) {
        state_warm = -1; // demote double-penalty
        return; // empty-handed - skip a turn
    }

*/

    if ( (state_warm ==  0) && ((uint8_t) *buf != 0x77) ) { // ! 'w'
        state_warm = -1;
        return;
    }

    if ( (state_warm == 0) && ((uint8_t) *buf == 0x77) ) { // 'w'
        // io_write(io, (uint8_t *) "!w!",  3);
        state_warm = 0x77; // first level gained
        return;
    }

    if ( (state_warm == 0x77) && ((uint8_t) *buf == 0x61) ) { // "wa..."
        // io_write(io, (uint8_t *) "!a!",  3);
        state_warm = 0x61; // second level gained
        return;
    }

    if ( (state_warm == 0x61) && ((uint8_t) *buf == 0x72) ) {  // "war.."
        // io_write(io, (uint8_t *) "!r!",  3);
        state_warm = 0x72; // third level gained
        return;
    }

    if ( (state_warm == 0x72) && ((uint8_t) *buf == 0x6d) ) {  // "warm."
        io_write(io, (uint8_t *) "  !warm! ",  9);
        state_warm = 0x6d; // fourth level gained
        return;
    }

    if ( (state_warm == 0x6d) && ((uint8_t) *buf == 0x0d) ) {  // "warmCR"
        io_write(io, (uint8_t *) " !reboot! ", 10);
        state_warm = 0xfd; // fifth level gained
        _warm();
        return; // shouldn't reach this
    }
    // if ( (state_warm == -2) || (state_warm == -1)) return; // preserve penalty
    state_warm = 0; // sieve fall-through
}

