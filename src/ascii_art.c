// Wed Aug 29 04:49:35 UTC 2018

#include <atmel_start.h>
#include <string.h>
#include "serial_io.h"

char ascii_art_buf[79];

void f_ascii_iow(void) {
    io_write(io, (uint8_t *)ascii_art_buf, strlen(ascii_art_buf));
    io_write(io, (uint8_t *)"\r\n", 2);
}

void forth_ascii(void) {
    _cr(); _cr(); // clear the decks

    strcpy(ascii_art_buf,
        "   ad88                               88           "
        ); f_ascii_iow();


    strcpy(ascii_art_buf,
        "  d8\"                           ,d    88           "
        ); f_ascii_iow();

    strcpy(ascii_art_buf,
        "  88                            88    88           "
        ); f_ascii_iow();

    strcpy(ascii_art_buf,
        "MM88MMM ,adPPYba,  8b,dPPYba, MM88MMM 88,dPPYba,   "
        ); f_ascii_iow();

    strcpy(ascii_art_buf,
        "  88   a8\"     \"8a 88P'   \"Y8   88    88P'    \"8a  "
        ); f_ascii_iow();

    strcpy(ascii_art_buf,
        "  88   8b       d8 88           88    88       88  "
        ); f_ascii_iow();

    strcpy(ascii_art_buf,
        "  88   \"8a,   ,a8\" 88           88,   88       88  "
        ); f_ascii_iow();

    strcpy(ascii_art_buf,
        "  88    `\"YbbdP\"'  88           \"Y888 88       88  "
        ); f_ascii_iow();
    
    _cr(); _cr(); // some eye relief
}

/*

"   ad88                               88           "
"  d8"                           ,d    88           "
"  88                            88    88           "
"MM88MMM ,adPPYba,  8b,dPPYba, MM88MMM 88,dPPYba,   "
"  88   a8"     "8a 88P'   "Y8   88    88P'    "8a  "
"  88   8b       d8 88           88    88       88  "
"  88   "8a,   ,a8" 88           88,   88       88  "
"  88    `"YbbdP"'  88           "Y888 88       88  "
*/

