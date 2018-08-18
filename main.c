#include <atmel_start.h>
#include "driver_examples.h"
#include "pins.h"

#define WASTED_TIME 21040

void waste(void) { // time and resources
    for (volatile int i=(8 * WASTED_TIME); i>0; i--) {
    }
}

void blink(void) {
    PORT->Group[PORTA].OUTTGL.reg  = (uint32_t)(1 << 17); // PA17 //    13 pintoggle // D13
    waste();
    PORT->Group[PORTA].OUTTGL.reg  = (uint32_t)(1 << 17);
    waste(); waste();
}

void shortpinwaste(void) { // short LED flasher
        for (int index = 8; index > 0; index--) blink();
}

void pinwaste(void) {
    for (int ji = 3; ji > 0; ji--) {
        for (int index = 8; index > 0; index--) blink();
        waste(); waste(); waste(); waste();
        waste(); waste(); waste(); waste();
        for (int index = 8; index > 0; index--) blink();
        waste(); waste(); waste(); waste();
        waste(); waste(); waste(); waste();
    }
}

int main(void) {
    /* Initializes MCU, drivers and middleware */
    atmel_start_init(); // calls system_init() from driver_init.c
    // init_mcu();

    pins_setup();

    // USART_0_example();

    // pinwaste(); // LED flasher
    shortpinwaste();

    // turn on LED once and for all -- cannot attend to it further:
    PORT->Group[PORTA].OUTSET.reg |= (uint32_t)(1 << 17); // PA17 //  1 13 pinwrite  // D13 

    // toggle D11 forever:
    while (1) {
        toggle_d11(); // 766 ns / 1.3 MHz
    }
}
