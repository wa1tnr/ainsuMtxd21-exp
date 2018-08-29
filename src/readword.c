#include "common.h"
#include "getKey.h"
// #include "driver_examples.h"
#include "serial_io.h"

// costs a bit more than 1kb:
#include "stdlib.h"

int crlfstate = 0; // differentiate when ascii 13 is entered to the terminal

uint8_t pos = 0;

/* Is the word in tib a number? */
int isNumber() {
    char *endptr;
    strtol(tib, &endptr, 0);
    if (endptr == tib) return 0;
    if (*endptr != '\0') return 0;
    return 1;
}

/* Convert number in tib */
int number() {
  char *endptr;
  return (int) strtol(tib, &endptr, 0);
}

void printing(void) {
    uint8_t ch_read = (uint32_t) ch[0];

    if (ch_read == 13) {
        crlfstate = -1; // raise crlfstate TRUE
        _spc(); // do not print a cr here!
    } else {
        if (ch_read != 32) { // a space delimiter
            io_write(io, (uint8_t *) ch, 1); // most chars echo TODO
        } else { // it's a space
            _spc(); // wrong comment: may need echo on some terminals TODO
        }
    }
}

void throw_(void) { }

uint8_t reading(void) {
    getKey();
    printing();
    uint8_t ch_read = (uint32_t) ch[0];
    if (ch_read == '\n') {
        _cr();
        return 1;
    }
    if (ch_read == '\r') return 0; // return 0: move onto the next word

/*
    if (ch_read == '\010') { // backspace
*/

    if (ch_read == ' ')  return 0;
    if ((ch_read == '\010')||(ch_read == '\177')) { // backspace
        if (pos == 0) throw_();
        tib[pos--] = 0;
        tib[pos] = 0;

        if (ch_read == '\177') {
            io_write(io, (uint8_t *) "\010", 1);
        }


        _spc();
        io_write(io, (uint8_t *) "\010", 1);



        return 1; // return 1: make the 'while (reading())' last a while longer!
    }
    if (pos < maxtib) {
        tib[pos++] = ch_read; // append
        tib[pos] = 0; // terminate
    }
    return 1; // ain't done yett..
}

void readword(void) {
    pos = 0;
    tib[0] = 0;
    while (reading());
}

/*

 $ diff readword.c readword.c__newer 
55c55
<     if (ch_read == '\010') { // backspace
---
>     if ((ch_read == '\010')|(ch_read == '\177')) { // backspace
 $ 

*/


