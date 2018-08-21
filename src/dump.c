/* dump.c */
/* 15 Aug 2018 20:21 UTC */
/* wa1tnr, Connecticut USA */
/* LICENSE: LGPL v2.1 */

#include "driver_examples.h"
#include "common.h"
#include <string.h>

// lower boundary of the memory to examine
#define LBOUND 0x1d10+0x10
#define UBOUND  0x1420

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
    io_write(io, (uint8_t *)"\040", 1); // SPACE ASCII 32 0x20
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
    io_write(io, (uint8_t *)"  ", 2);

    for (int i = 0; i < 16; i++) {
        char c = *ram++;

        byte_r = (uint8_t) c; // global

        parsed_hi(); // print upper nybble out serial port

        parsed_low(); // print lower nybble out serial port
    } // for

    ram = (char*)p;
    io_write(io, (uint8_t *)"  ", 2);
    for (int i = 0; i < 16; i++) {
        buffer[0] = *ram++;
        if (buffer[0] > 0x7f || buffer[0] < ' ') buffer[0] = '.'; // the dot for unprintable chars
        buffer[1] = '\0';

     // print the ascii translation chars on the right margin, one
     // at a time:
        io_write(io, (uint8_t *)buffer, 1); // compiles cleanly
    }
    // forth: push(p + 16);
    COUNTER = COUNTER + 16;
    return (uint8_t *)p;
}
