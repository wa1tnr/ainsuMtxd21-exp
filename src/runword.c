// Sun Aug 26 21:43:30 UTC 2018

/* runword.c */

#include <atmel_start.h>
#include <string.h>
#include "common.h"
#include "dict.h"
#include "serial_io.h"
#include "stack_ops.h"
#include "readword.h"
#include "debugging.h"
#include "getKey.h"

char spcbuf[2];
char crbuf[2];

void runword(void) {
    int place = locate();
    if ( DEBUG_FORTH_DICT_PRIMITIVES ) {
        io_write(io,     (uint8_t *)" ~runword place echo~ ", 22);
    }
    if ( DEBUG_FORTH_DICT_PRIMITIVES ) {
        io_write(io, (uint8_t *)    " ~runword d0t~ ", 15);
                             /*  1234567890123456789012345678901234567890 */
    }
    if ( DEBUG_FORTH_DICT_PRIMITIVES ) {
        io_write(io, (uint8_t *)    " ~Place~ ", 9);
        push(place); dot();
    }
    // 5 #define LOCATE_BOUNDS_ERR -11
    if ((place != LOCATE_BOUNDS_ERR) // 0
        & (place < (entries - 1))) { // if ((place != -11) & ..
        if ( DEBUG_FORTH_DICT_PRIMITIVES ) {
            io_write(io, (uint8_t *)" ~runword place fgh~ ", 20);
        }
        if ( DEBUG_FORTH_DICT_PRIMITIVES ) {
            push(place); dot();
        }
        dictionary[place].function(); // meat on the bone
        _ok();
        return;
    }

    if (isNumber()) {
        push(number()); // pivotal change
        if ( DEBUG_FORTH_DICT_PRIMITIVES ) {
            io_write(io, (uint8_t *)" ~runword isNumber 773~ ", 24);
        }
        _ok();
        return;
    }

    if (strlen(tib) == 0) { // reliable test for no input on a cr
        // io_write(io, (uint8_t *)"  strlen(tib) == 0 ", 19);
        _ok(); return;
    }

/*
    strcpy(crbuf, (char *)'\015');

    if (strcmp(tib, crbuf)) { io_write(io, (uint8_t *)" ~strcmp compared~ ", 19); _ok(); return; }

    if (crlfstate == -1) { io_write(io, (uint8_t *)" ~crlfstate is -1~ ", 19); _ok(); return; }

    if (crlfstate == 0) { io_write(io, (uint8_t *)" ~crlfstate is  0~ ", 19); _que(); return; }

    // strcpy(spcbuf, " ");

    // strcpy(crbuf, "\015\0");

    // if (!strcmp(tib, crbuf)) { _ok(); return; }

    // if (strcmp(tib, spcbuf)) { nop(); return; }

    // if (crlfstate == -1) { _cr(); _cr(); _cr(); }

*/
    _que(); // Serial.println("?");
}
