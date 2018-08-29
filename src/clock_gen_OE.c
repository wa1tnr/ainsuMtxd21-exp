#include <atmel_start.h>
#include "pins.h"
#include "clock_gen_OE.h"

// 24 August SAMD51 Metro M4 Express
void clock_gen_oe(void) { // ainsu new idiom 24 August 2018
#ifndef OMIT_GCLK0_OE_PINMUX_SETUP

    // Possible pins for SAMD21, for this output, are:

    // PA14  PA27  PA28  PA30
    // PB14  PB22

    // Pin D4 (which is also PA14) on SAMD51 (Feather M4 Express)
    // is known to work, also.

    // PA14 (board D2) Metro M0 Express, only // ainsuforth wa1tnr TODO

    // configure PA14 (board D2) as GCLK_IO[0] output of main clock generator,
    // to confirm 48 MHz operation
    // set pin as output

    // SAMD51

    // Metro M4 Express:

    //     PA14 MISO
    //     PA30 SWCLK
    //     PB14 D5
    //     PB22 NEOPIX

    // Clock generation output can be configured on the mux for any
    // of those four pins.  D5 is a good candidate.

#if defined ADAFRUIT_METRO_M4_EXPRESS
    PORT->Group[PORTB].DIRSET.reg  = (uint32_t)(1 << 14); // PB14 //  1  5 pinmode  // D5 // SAMD51

    PORT->Group[PORTB].PINCFG[14].bit.PMUXEN = 1; // enable the peripheral mux for this pin

    PORT->Group[PORTB].PMUX[(14>>1)].bit.PMUXE
        = MUX_PB14M_GCLK_IO0; // select the GCLK_IO0 peripheral function

    GCLK->GENCTRL[0].bit.OE = 1; // enable output from clock generator 0
#endif // METRO_M4

#if defined ADAFRUIT_METRO_M0_EXPRESS
    PORT->Group[PORTA].DIRSET.reg  = (uint32_t)(1 << 14); // PA14 //  1  2 pinmode   //  D2

    // enable the peripheral mux for this pin
    PORT->Group[PORTA].PINCFG[14].bit.PMUXEN = 1; // enable the peripheral mux for this pin

    PORT->Group[PORTA].PMUX[(14>>1)].bit.PMUXE
        = MUX_PA14H_GCLK_IO0; // select the GCLK_IO0 peripheral function

    // do this in ./config/hpl_gclk_config.h:
    // GCLK->GENCTRL[0].bit.OE = 1; // enable output from clock generator 0
#endif // METRO_M0

#endif // OMIT
}
