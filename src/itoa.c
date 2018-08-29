// Sat Aug 25 19:30:14 UTC 2018

/*
  LICENSE: LGPL v2.1 Arduino LLC > Adafruit.com > you and me ;)

  adopted for ainsMtxd51 by wa1tnr 25 August 2018

  .arduino15/packages/adafruit/hardware/samd/1.2.1/cores/arduino/itoa.c

  Copyright (c) 2014 Arduino LLC.  All right reserved.
*/

#include <atmel_start.h>
#include "common.h"
#include "serial_io.h"
#include <string.h>

char pr_strn[stackbuflen];

// print string - weak naming.  review. TODO wa1tnr
int input_intgr = 0; // input integer - also a weak name. ;)  TODO wa1tnr

void prelude_to_cleo(void) {
    for (int jk = 7; jk > 0; jk--) {
        io_write(io, (uint8_t *)"m", 1);
    }
}

/* reverse:  reverse string s in place */
static void reverse(char s[]) {
    int i, j ;
    char c ;
    for ( i = 0, j = strlen(s)-1 ; i < j ; i++, j-- ) {
        c = s[i] ;
        s[i] = s[j] ;
        s[j] = c ;
    }
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[]) {
    int i, sign ;
    if ( (sign = n) < 0 ) { // record sign
        n = -n; // make n positive
    }
    i = 0;
    do { // generate digits in reverse order
        s[i++] = n % 10 + '0'; // get next digit
    } while ((n /= 10) > 0) ; // delete it
    if (sign < 0 ) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}

void call_me_now_ms_cleo(void) { // call me now for your free reading
    prelude_to_cleo(); // test basic io_write() functionality

    pr_strn[0] = (uint32_t) "\0";
    input_intgr = 5280; // feet in a mile

    // extern void itoa( int n, char s[] )
    itoa (input_intgr, pr_strn);

    // pr_strn is populated now.
    io_write(io, (uint8_t *)pr_strn, 4);
}

/*
  .arduino15/packages/adafruit/hardware/samd/1.2.1/cores/arduino/itoa.c

  Copyright (c) 2014 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
