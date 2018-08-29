/* nyb_stack.c */
/* 20 Aug 2018 21:50 UTC */
/* wa1tnr, Connecticut USA */
/* LICENSE: LGPL v2.1 */

/*
 *  program:  load a value into an int (test_byte),
 *
 *            then dump the ram that holds that value,
 *            to examine how that value was represented
 *            in system memory.
 */

/* question: does &++ make sense at all?              */
/*                                                    */
/* intent:  add '1' to the contents of a variable     */

// #include "driver_examples.h"
#include "serial_io.h"
#include "common.h"
#include <string.h>

int nyb_stack = 0;
int rbyte_n = 0;

char byte_r;

/* dig this:
 *
 * Rather than become reinventive, reused code was
 * differentiated by (simply) appending '_n' to the
 * names of functions (and variables!)
 *
 * The intent, here, is to keep things simple, early
 * on (this isn't the time to think about other,
 * legitimate concerns, that compete with those concerns
 * that are more immediate).
 *
 * Factoring, later on, seems likely. ;)
 */

void ascii_emit_n(void) { // preload rbyte_n with a value 0-15 decimal
    if (rbyte_n ==   0) io_write(io, (uint8_t *)"0", 1);
    if (rbyte_n ==   1) io_write(io, (uint8_t *)"1", 1);
    if (rbyte_n ==   2) io_write(io, (uint8_t *)"2", 1);
    if (rbyte_n ==   3) io_write(io, (uint8_t *)"3", 1);

    if (rbyte_n ==   4) io_write(io, (uint8_t *)"4", 1);
    if (rbyte_n ==   5) io_write(io, (uint8_t *)"5", 1);
    if (rbyte_n ==   6) io_write(io, (uint8_t *)"6", 1);
    if (rbyte_n ==   7) io_write(io, (uint8_t *)"7", 1);

    if (rbyte_n ==   8) io_write(io, (uint8_t *)"8", 1);
    if (rbyte_n ==   9) io_write(io, (uint8_t *)"9", 1);
    if (rbyte_n == 0xa) io_write(io, (uint8_t *)"A", 1);
    if (rbyte_n == 0xb) io_write(io, (uint8_t *)"B", 1);

    if (rbyte_n == 0xc) io_write(io, (uint8_t *)"C", 1);
    if (rbyte_n == 0xd) io_write(io, (uint8_t *)"D", 1);
    if (rbyte_n == 0xe) io_write(io, (uint8_t *)"E", 1);
    if (rbyte_n == 0xf) io_write(io, (uint8_t *)"F", 1);
}

/*
  $ echo "0 1 2 3 4 5 6 7 8 9 A B C D E F" | hexdump -C
  00000000  30 20 31 20 32 20 33 20  34 20 35 20 36 20 37 20  |0 1 2 3 4 5 6 7 |
  00000010  38 20 39 20 41 20 42 20  43 20 44 20 45 20 46 0a  |8 9 A B C D E F.|
*/


uint8_t* parsed_low_n(void) {
    char byte_s = byte_r;
    rbyte_n = byte_s; // rbyte_n is a working copy;
    rbyte_n = byte_s & 0x0f; // mask upper nybble - two ampersands gives a boolean
    ascii_emit_n();
    io_write(io, (uint8_t *)"\040", 1); // SPACE ASCII 32 0x20
    return (uint8_t *) rbyte_n;
}

uint8_t* parsed_hi_n(void) {
    char byte_s = byte_r;
    rbyte_n = byte_s;
    rbyte_n = byte_s & 0xf0; // lower nybble masked
    rbyte_n = rbyte_n >> 4;
    ascii_emit_n();
    return (uint8_t *) rbyte_n;
}

int COUNTER_N = 0;

uint8_t* ndump(void) { // nybble dump

    //   int test_byte = 0xdf;
    uint32_t test_byte = 0xc0ffeeca; // sample int to place into ram

/*
 *  sample run
 *
 *  uint32_t test_byte = 0xc0ffeeca; // sample int to place into ram
 *
 *  DD EE FF C0 00 00 00 00 00 21 00 00 2A 00 00 00   .........!..*...
 *
 *  old code:
 *  int test_byte = 0xdf; // sample int to place into ram
 *
 *  No program changes were required going from
 *          'int test_byte = 1'
 *  to 'uint32_t test_byte = 0xc0ffeeca'.
*/

    char buffer[5] = "";
    char *ram;

    ram = (char*) &test_byte;

    io_write(io, (uint8_t *)"\015\012", 2); // CRLF
    io_write(io, (uint8_t *)"  ", 2);

    for (int i = 0; i < 16; i++) {
        char c = *ram++;
        byte_r = (uint8_t) c; // global
        parsed_hi_n(); // print upper nybble out serial port
        parsed_low_n(); // print lower nybble out serial port
    } // for

    ram = (char*) &test_byte;

    io_write(io, (uint8_t *)"  ", 2);
    for (int i = 0; i < 16; i++) {
        buffer[0] = *ram++;
        if (buffer[0] > 0x7f || buffer[0] < ' ') buffer[0] = '.'; // the dot for unprintable chars
        buffer[1] = '\0';

     // print the ascii translation chars on the right margin, one
     // at a time:
        io_write(io, (uint8_t *)buffer, 1);
    }
    // forth: push(p + 16);
    COUNTER_N = COUNTER_N + 16;
    return (uint8_t *)test_byte;
}
