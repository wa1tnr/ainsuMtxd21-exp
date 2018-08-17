#include <atmel_start.h>
#include "pins.h"

void waste(void) { // time and resources
    for (volatile int i=(8 * 2104); i>0; i--) {
    }
}

void blink(void) {
    PORT->Group[PORTA].OUTTGL.reg  = (uint32_t)(1 << 17); // PA17 //    13 pintoggle // D13
    waste();
    PORT->Group[PORTA].OUTTGL.reg  = (uint32_t)(1 << 17);
    waste(); waste();
}

int main(void) {
    /* Initializes MCU, drivers and middleware */
    pins_setup();

    /* Replace with your application code */
    while (1) {
        blink();
        toggle_d11();
    }
}
