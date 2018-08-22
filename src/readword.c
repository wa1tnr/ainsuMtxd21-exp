#include "common.h"
#include "getKey.h"

void printing(void) {
}

uint8_t reading(void) {
    getKey();
    printing();
    return 1;
}

void readword(void) {
    while (reading());
}
