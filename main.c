#include <atmel_start.h>
#include "driver_examples.h"
#include "pins.h"
#include "src/dump.h"

void delays(void) { // delay some
    for (volatile int i=1299999; i>0; i--) {
        // empty loop
    }
}

void blink_two(void) {
    // clear first
    PORT->Group[PORTA].OUTCLR.reg  = (uint32_t)(1 << 17); // PA17 //  0 13 pinwrite  // D13
    for (int blinks=2; blinks >0; blinks--) {
        PORT->Group[PORTA].OUTTGL.reg  = (uint32_t)(1 << 17); // PA17 //    13 pintoggle // D13
        delays();
    }
}


void ldelays(void) {
    for (int ie=7; ie >0; ie--) {
        delays();
    }
}

void blink_awhile(void) {

    for (int iter=5; iter >0; iter--) {
        blink_two();
    }

/*
    ldelays();

    for (int iter=3 ; iter >0; iter--) {
        blink_two();
    }

    ldelays();

    for (int iter=3 ; iter >0; iter--) {
        blink_two();
    }

    ldelays();
*/

}

int main(void)
{
    uint8_t* rram = 0;
    int q = 0;
    /* Initializes MCU, drivers and middleware */
    atmel_start_init();
    SystemInit();
    pins_setup(); // initialize GPIO D13 PA17

    // blink_awhile(); // is the clock running?

    USART_0_example();

    // rram = srdump();

    rram = cdump();
    rram = cdump();
    rram = cdump();
    rram = cdump();
    rram = cdump();
    rram = cdump();
    rram = cdump();
    rram = cdump();



    q = (int)rram;
    if (q > 2)  q = 2;
    if (q < 1)  q = 2;
    for (volatile int i=-1; i<q; i++) {
        blink_two();
        // ldelays();
    }
    /* Replace with your application code */

    while (1) {
        toggle_d11();
    }
}
