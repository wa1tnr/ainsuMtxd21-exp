/* dump.c */
/* 15 Aug 2018 20:21 UTC */
/* wa1tnr, Connecticut USA */
/* LICENSE: LGPL v2.1 */

#include "driver_examples.h" // "examples/driver_examples.h"
#include "common.h"

#include <string.h>


// void say_something(void) { }

// lower boundary of the memory to examine
#define LBOUND 0x1d10+0x10
#define UBOUND  0x1420

int rbyte = 0;
char byte_r;

void ascii_emit(void) { // preload rbyte with a value 0-15 decimal
    if (rbyte == 0) io_write(io, (uint8_t *)"0", 1); // '0'
    if (rbyte == 1) io_write(io, (uint8_t *)"1", 1); // '1'
    if (rbyte == 2) io_write(io, (uint8_t *)"2", 1); // '2'
    if (rbyte == 3) io_write(io, (uint8_t *)"3", 1); // '3'
    if (rbyte == 4) io_write(io, (uint8_t *)"4", 1); // '4'
    if (rbyte == 5) io_write(io, (uint8_t *)"5", 1); // '5'
    if (rbyte == 6) io_write(io, (uint8_t *)"6", 1); // '0'
    if (rbyte == 7) io_write(io, (uint8_t *)"7", 1); // '0'
    if (rbyte == 8) io_write(io, (uint8_t *)"8", 1); // '0'
    if (rbyte == 9) io_write(io, (uint8_t *)"9", 1); // '0'
    if (rbyte == 0xa) io_write(io, (uint8_t *)"A", 1); // 'A'
    if (rbyte == 0xb) io_write(io, (uint8_t *)"B", 1); // 'B'
    if (rbyte == 0xc) io_write(io, (uint8_t *)"C", 1); // 'C'
    if (rbyte == 0xd) io_write(io, (uint8_t *)"D", 1); // 'D'
    if (rbyte == 0xe) io_write(io, (uint8_t *)"E", 1); // 'E'
    if (rbyte == 0xf) io_write(io, (uint8_t *)"F", 1); // 'F'
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
    ascii_emit();
    io_write(io, (uint8_t *)"\040", 1); // SPACE ASCII 32 0x20
    return (uint8_t *) rbyte;
}

uint8_t* parsed_hi(void) { // parse it out
    int rbyte = 0;
    char byte_s = byte_r;
    rbyte = byte_s; // rbyte is a working copy;
    rbyte = byte_s & 0xf0; // mask lower nybble
    rbyte = rbyte >> 4;
    ascii_emit();
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
