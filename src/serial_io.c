// Wed Aug 29 23:29:01 UTC 2018
// On branch KM_converser_d21

/* wa1tnr - August, 2018 LGPL v2.1 */

// previous:
// Wed Aug 29 22:55:07 UTC 2018
// On branch KM_converser_TRIAL_run-

// Wed Aug 29 05:07:42 UTC 2018
// On branch xKM_converser_d51-nn-

#include "serial_io.h"
#include "driver_init.h"
#include "common.h"
#include "getKey.h"
#include "utils.h"
#include "warm.h"
#include "readword.h"
#include "runword.h"
#include "stack_ops.h"
#include "debugging.h"
#include "dict_common.h"

#define timeStamp(t,l)   "Wed Aug 29 23:29:01 UTC 2018\r\n\r\n", 32

/*
#define branchStamp(b,l) "KM_converser_TRIAL_run-  ", 25
*/

#define branchStamp(b,l) "KM_converser_d21         ", 25

/*
#define branchStamp(b,l) "KM_converser_d51         ", 25
*/

/*
#define branchStamp(b,l) "master                   ", 25
*/

struct io_descriptor *io;

void usart_sync_get_desc(void) {
    usart_sync_get_io_descriptor(&USART_0, &io);
}

void usart_sync_enbl(void) {
    usart_sync_enable(&USART_0);
}

void bg_black(void)   { // background black
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\064\060", 2); // 40 - blue black
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void bg_red(void)    { // background red
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\064\061", 2); // 41 - red bg
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void bg_blue(void)   { // background blue
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\064\064", 2); // 44 - blue bg
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void color_reset(void) {  // reset color
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\060", 1);     // 0
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void fg_white(void) {
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\060", 1);     // 0
    io_write(io, (uint8_t *)"\073", 1);     // ;  semicolon
    io_write(io, (uint8_t *)"\061", 1);     // 1
    io_write(io, (uint8_t *)"\073", 1);     // ;  semicolon
    io_write(io, (uint8_t *)"\063\067", 2); // 37 - white  fg
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void fg_yellow(void) { // foreground yellow
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\063\063", 2); // 33 - yellow fg
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

/**
 * Example of using USART_0 to write "Hello World" using the IO abstraction.
 */

uint8_t *buf;

void _que(void) {
    io_write(io, (uint8_t *) "? ",         1);
    _spc();
}

void _ok(void) {
    if ( DEBUG_FORTH_DICT_PRIMITIVES ) {
        io_write(io, (uint8_t *) " ~serial_io.c LINE 73: ",  23);
                               // 123456789012345678901234567890123456789012345
    }
    // primary OK prompting at the moment, is here:
    // io_write(io, (uint8_t *) "okay", 4);
    if (crlfstate == -1) {
        io_write(io, (uint8_t *) " ok\r\n", 5); // echo TODO \r\n on some terminals
        crlfstate = 0;
    }
}

void filter(void) {

    // capture_warm();

    /* stanza -- control H */
    if ((uint8_t) *buf == 8) { // Control H
        io_write(io, (uint8_t *) "\010",  1);
        io_write(io, (uint8_t *) " ",  1);
        return;
    }

    /* stanza -- rubout */
    if ((uint8_t) *buf == 127) { // Control H
        io_write(io, (uint8_t *) "\010",  1);
        io_write(io, (uint8_t *) " ",  1);
        io_write(io, (uint8_t *) "\010",  1); // rubout needs to travel to the left here
        return;
    }

    /* stanza -- CR */
    if ((uint8_t) *buf == 13) { // CR or 0x0d
        // io_write(io, (uint8_t *) " ok",  3); // need to not do this here
        io_write(io, (uint8_t *) "\015",  1); // 0x0d
        io_write(io, (uint8_t *) "\012",  1); // 0x0a // your terminal may want differently
        return;
    }
}

void _bkbar(void) {
    io_write(io, (uint8_t *) "|",         1);
}

void _spc(void) {
    io_write(io, (uint8_t *) " ",         1);
}

void _cr(void) {
    io_write(io, (uint8_t *) "\r\n",         2);
}

void cr(void) {
    _cr();
}

void USART_0_example_upper(void) {
    usart_sync_get_desc();
    usart_sync_enbl();
    _cr();
}

void dispatcher_simple_int(void) {
    // int rval = number();
    if (number() == 911) { // help
        io_write(io, (uint8_t *) "\r\n\r\n     911 - help\r\n",  21);
        io_write(io, (uint8_t *) "     211 - reboot (warm)\r\n",  26);
    }
    if (number() == 211) _warm();
}

void USART_0_example_lower(void) {
    _cr();

#undef HAS_HELLO_INTERPRETER
#define HAS_HELLO_INTERPRETER
#ifndef HAS_HELLO_INTERPRETER

    io_write(io, (uint8_t *) "USART_0_example_upper() .. completes.\r\n", 39); // is alive
                           // 123456789012345678901234567890123456789012345
                           //         10        20        30
#endif // #ifndef HAS_HELLO_INTERPRETER

#ifdef HAS_HELLO_INTERPRETER

    io_write(io, (uint8_t *)
        "Program is configured for 38400 bps speed.\r\n\r\n",        46);
    io_write(io, (uint8_t *)
    //  "Target MCU board is Adafruit Metro M4 Express.\r\n\r\n",    50);

        "Target MCU board is Adafruit Feather M0 Express.\r\n\r\n",  52);

    color_reset();

    io_write(io, (uint8_t *)
        "UART pins TX and RX used with CP2104 bridge.\r\n\r\n",      48);

    io_write(io, (uint8_t *) branchStamp(t,l));

/*
    io_write(io, (uint8_t *)
        "xKM_converser_d51-jj-atmel_start_verif-    ", 43); // private branch - see KM_converser_d51 instead
*/
    // PRESERVE BRANCH_STAMP for lineage verification:
    //  "xKM_converser_d51-gg-    ", 25); // private branch - see KM_converser_d51 instead

    //  12345678901234567890123456789012345678901234567890
    // "KM_converser_d51         ", 25);

    // prep for merge into master, 25 Aug 20:58 UTC:
    // "On branch master         ", 25); // reflect that this is really branch master

/*
    io_write(io, (uint8_t *)
        "SMUDGE BIT SET   ", 17); // SMUDGE (means nothing other than 'this is different'
*/

    io_write(io, (uint8_t *) timeStamp(t,l));

    // PRESERVE TIMESTAMP for lineage verification:
    //  "Mon Aug 27 04:04:40 UTC 2018\r\n\r\n",                      32);

    /*   12345678901234567890123456789012345678901234567890
                 10        20        30        40        50 */

    bg_blue();
    fg_white();
    bg_red();
    io_write(io, (uint8_t *)  "  ainsuForth MTX  ",  18);
    //     12345678901234567890123456789012345678901234567890
    color_reset();

    bg_black();
 // io_write(io, (uint8_t *)"    type 'words': \r\n\r\n",  24);
    io_write(io, (uint8_t *)"                  \r\n\r\n",  22);
    //             12345678901234567890123456789012345678901234567890
    bg_black();

    fg_yellow(); // color it!

    while(-1) { // endless loop, read one char, write one char (echo)
        readword();
        runword();
        if ( DEBUG_FORTH_DICT_PRIMITIVES ) {
            io_write(io, (uint8_t *)" ~readword~ ", 12);
        }
/*
        if (isNumber()) {
            if ( DEBUG_FORTH_DICT_PRIMITIVES ) {
                // io_write(io, (uint8_t *)"  ~isNumber~  ", 14);
                push(number());
                dot(); // the forth word 'dot' ( a '.' by itself on the command line)
            }
            dispatcher_simple_int(); // command processor
        }
        tib[0] = ch[0];
        buf = (uint8_t *)tib;
        filter();
        io_write(io, (uint8_t *)tib, 1); // 1  is also length
        capture_warm();
*/
    }
#endif // #ifdef HAS_HELLO_INTERPRETER
}
