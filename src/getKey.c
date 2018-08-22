// Wed Aug 22 18:00:54 UTC 2018
/* wa1tnr - August, 2018 LGPL v2.1 */

// On branch KM_converser_aa-
//     On branch xKM_converser_aa-br-bb-

// #include "../common.h"
#include "common.h"
#include "driver_examples.h"

// maxtib defined in common.h

/* Terminal Input Buffer for interpreter */
char tib[maxtib];

void _USART_read(void) { // hardware implementation-dependent keystroke reader
    // getKey:
    io_read(io,  (uint8_t *)tib, 1); // 1  is length
}

void getKey(void) { // hardware-independent wrapper
    _USART_read();
}
