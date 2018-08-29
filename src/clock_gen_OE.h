// Removes/includes all code found in clock_gen_oe()

// swap:
#undef  OMIT_GCLK0_OE_PINMUX_SETUP
#define OMIT_GCLK0_OE_PINMUX_SETUP

extern void clock_gen_oe(void); // { // ainsu new idiom 24 August 2018
