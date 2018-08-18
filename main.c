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

int main(void) {
    /* Initializes MCU, drivers and middleware */
    // atmel_start_init();
    SystemInit();
    // SystemCoreClockUpdate();
    // init_mcu();
    pins_setup();

    // USART_0_example();

    /* Replace with your application code */
    while (1) {
        // blink();
        toggle_d11();
    }
}
