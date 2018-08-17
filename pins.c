// Sun Aug 12 12:34:02 UTC 2018
#include "atmel_start.h"
#include "pins.h"

void pins_setup(void) {
    PORT->Group[PORTA].DIRSET.reg  = (uint32_t)(1 << 17); // PA17 //  1 13 pinmode   // D13
    PORT->Group[PORTA].OUTTGL.reg  = (uint32_t)(1 << 17); // PA17 //    13 pintoggle // D13
    PORT->Group[PORTA].OUTSET.reg |= (uint32_t)(1 << 17); // PA17 //  1 13 pinwrite  // D13
    PORT->Group[PORTA].OUTCLR.reg  = (uint32_t)(1 << 17); // PA17 //  0 13 pinwrite  // D13
}
