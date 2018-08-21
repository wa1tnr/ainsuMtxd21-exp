/* dump.c */
/* 21 Aug 2018 21:23 UTC */
/* wa1tnr, Connecticut USA */
/* LICENSE: LGPL v2.1 */

// On branch KM_converser_aa-

#include "driver_examples.h"
#include "common.h"
#include <string.h>

// lower boundary of the memory to examine
// #define LBOUND 0x1d10+0x10

// #define LBOUND 0x20000000+(0x0100 * 2)

// SRAM     // #define LBOUND 0x20000000+(0x0100 * 0)
// OTHER    // #define LBOUND 0x40000000+(0x0100 * 0)

// change the last number to any positive integer, for an offset:
// #define LBOUND 0x20000000+(0x0100 * 0)

#define LBOUND 0x1d10+0x10 // Adafruit

/* see main.c for how many lines of memory to dump.
   It may be a very large number!

   dump.c  on the other hand provides a memory dump,
           of a single line of 16 bytes, when asked
           to do so. */

uint32_t  rbyte = 0;
char      byte_r;

void new_ascii_emit(void) {
    int       char_r   =  '0';
    char     *cbyte;

    rbyte = rbyte + 0x30; // normalize (in ASCII) for 0-9

    if (rbyte > 0x39) rbyte = rbyte + 7; // handle A-F

    cbyte = (char*) &rbyte;

    int df = (uint32_t) cbyte;

    char *dfbyte = (char*) df;

    char_r = (int)dfbyte;

    io_write(io, (uint8_t *) char_r, 1);
}

/*
  $ echo "0 1 2 3 4 5 6 7 8 9 A B C D E F" | hexdump -C
  00000000  30 20 31 20 32 20 33 20  34 20 35 20 36 20 37 20  |0 1 2 3 4 5 6 7 |
  00000010  38 20 39 20 41 20 42 20  43 20 44 20 45 20 46 0a  |8 9 A B C D E F.|
*/

uint8_t* parsed_low(void) {
    char byte_s = byte_r;
    rbyte = byte_s; // rbyte is a working copy;
    rbyte = byte_s & 0x0f; // mask upper nybble - two ampersands gives a boolean
    new_ascii_emit(); // ascii_emit();
 // io_write(io, (uint8_t *)"\040", 1); // SPACE ASCII 32 0x20
    return (uint8_t *) rbyte;
}

uint8_t* parsed_hi(void) {
    char byte_s = byte_r;
    rbyte = byte_s;
    rbyte = byte_s & 0xf0; // lower nybble masked
    rbyte = rbyte >> 4;

    new_ascii_emit(); // ascii_emit();
    return (uint8_t *) rbyte;
}

int COUNTER = 0;

/* dump 16 bytes of RAM in hex with ascii on the side */
uint8_t* cdump(void) {
    char buffer[5] = "";
    char *ram;
    int p = LBOUND+COUNTER ;
    ram = (char*)p;

    io_write(io, (uint8_t *)"\015\012", 2); // CRLF
 // io_write(io, (uint8_t *)"  ", 2);

    // address printing

    uint32_t adrs  = (uint32_t) ram;

    io_write(io, (uint8_t *)"$", 1);

    /* stanza */
    uint32_t digit = adrs & 0xff000000; // MSB - uppermost byte
    digit = digit >> 24;
    byte_r = (uint8_t) digit;
    parsed_hi();
    parsed_low();

    /* stanza */
    // uint32_t
    digit = adrs & 0x00ff0000;
    digit = digit >> 16;
    byte_r = (uint8_t) digit;
    parsed_hi();
    parsed_low();

    // may not want this here, formatting style decision:
    // io_write(io, (uint8_t *)":", 1);

    /* stanza */
    digit = adrs & 0x0000ff00;
    digit = digit >>  8;
    byte_r = (uint8_t) digit;
    parsed_hi();
    parsed_low();

    /* stanza */
    digit = adrs & 0x000000ff;
 // digit = digit >>  8;
    byte_r = (uint8_t) digit;
    parsed_hi();
    parsed_low();

    io_write(io, (uint8_t *)" ", 1);

    byte_r = 0; // clear it for next subprogram's reuse

    for (int i = 0; i < 16; i++) {
        char c = *ram++;

        byte_r = (uint8_t) c; // global

        parsed_hi(); // print upper nybble out serial port

        parsed_low(); // print lower nybble out serial port
        _spc();

        if (i == 7) _spc();
    } // for

    ram = (char*)p;


    io_write(io, (uint8_t *)"   ", 3); // white space column separating hex from ASCII

    /* FEATURE
    _bkbar(); // begin stanza
    */
    for (int i = 0; i < 16; i++) {
        buffer[0] = *ram++;
        // 0x7f is unprintable, so 0x7e
        if (buffer[0] > 0x7e || buffer[0] < ' ') buffer[0] = '.'; // the dot for unprintable chars
        buffer[1] = '\0';

     // print the ascii translation chars on the right margin, one
     // at a time:
        io_write(io, (uint8_t *)buffer, 1); // compiles cleanly
    }

    /* FEATURE
    _bkbar(); // end stanza
    */

    // forth: push(p + 16);
    COUNTER = COUNTER + 16;
    return (uint8_t *)p;
}
