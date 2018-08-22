#include "common.h"
#include "getKey.h"
#include "driver_examples.h"

void printing(void) {
    uint8_t ch_read = (uint32_t) ch[0];

    if (ch_read == 13) {
        _spc(); // do not print a cr here!
    } else {
        if (ch_read != 32) { // a space delimiter
            io_write(io, (uint8_t *) ch, 1);
        } else { // it's a space
            _spc();
        }
    }
}

uint8_t reading(void) {
    getKey();
    printing();
    return 1;
}

void readword(void) {
    while (reading());
}
